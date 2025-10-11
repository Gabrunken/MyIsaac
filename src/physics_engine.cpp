#include <physics_engine.hpp>
#include <cmath>

void PhysicsEngine::ProcessSpritePhysics(double deltaTime)
{
    for (Sprite* sprite : _sprites)
    {
        //For now i'll do a O(n^2) for collisions
        for (Sprite* checkingSprite : _sprites)
        {
            if (sprite == checkingSprite) continue;

            if (sprite->_collisionType != CollisionType::None)
            {
                Vector2 intersection = checkingSprite->_collisionType == CollisionType::Rect ? CheckForAABB(*checkingSprite, *sprite) : 0;
                if (intersection.x == 0 && intersection.y == 0) continue;
                Vector2 intersectionNormalized = intersection.GetNormalized();
                float relativeVelocity = Vector2::Dot(sprite->_velocity - checkingSprite->_velocity, intersectionNormalized);

                if (relativeVelocity > 0.0f) //I dont fucking know why i return, chatgpt says so.
                    return;

                Vector2 resolutionImpulse = intersectionNormalized * relativeVelocity;

                if (!sprite->_isTrigger)
                {
                    if (!sprite->_isStatic)
                    {
                        sprite->_rect.position -= intersection; //Resolve collisions
                        sprite->_velocity -= resolutionImpulse;
                    }
                }

                if (!checkingSprite->_isTrigger)
                {
                    if (!checkingSprite->_isStatic)
                    {
                        checkingSprite->_rect.position += intersection; //Resolve collisions
                        checkingSprite->_velocity += resolutionImpulse;
                    }
                }
            }
        }


        if (!sprite->enablePhysics) continue;

        sprite->_forcesAccumulated.y += _gravityAcceleration * sprite->_mass * sprite->gravityMultiplier;

        Vector2 acceleration = sprite->_forcesAccumulated * (sprite->GetInverseMass());
        sprite->_velocity += acceleration * deltaTime;
        sprite->_rect.position += sprite->_velocity * deltaTime;
        sprite->_forcesAccumulated = 0;
    }
}

Vector2 PhysicsEngine::CheckForAABB(Sprite& a, Sprite& b)
{
    Vector2 centerA = a.GetPositionCentered();
    Vector2 centerB = b.GetPositionCentered();

    Vector2 halfSizeA = a.GetScale() / 2.0f;
    Vector2 halfSizeB = b.GetScale() / 2.0f;

    float deltaX = centerA.x - centerB.x;
    float intersectionAmountX = (halfSizeB.x + halfSizeA.x) - std::fabs(deltaX);

    float deltaY = centerA.y - centerB.y;
    float intersectionAmountY = (halfSizeB.y + halfSizeA.y) - std::fabs(deltaY);

    if (intersectionAmountX <= 0.0f || intersectionAmountY <= 0.0f)
    {
        if (a._isColliding)
        {
            if (a._isTrigger)
            {
                a._onCollisionExitCallback(b);
                b._onCollisionExitCallback(a);
            }

            //This whole thing needs to be rebuilt...
            a._isColliding = false;
        }

        if (b._isColliding)

        return 0; //No intersection
    }

    //There is intersection, notify sprites
    if (!a._isColliding)
    {
        a._onCollisionEnterCallback(b);
        a._isColliding = true;
    }

    //Check for direction
    float directionX = deltaX < 0.0f? -1.0f : 1.0f;
    float directionY = deltaY < 0.0f? -1.0f : 1.0f;

    //Resolve collisions on only 1 axis, the most relevant.
    if (intersectionAmountX < intersectionAmountY)
        return {intersectionAmountX * directionX, 0.0f};
    else
        return {0.0f, intersectionAmountY * directionY};
}