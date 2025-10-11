#include <physics_engine.hpp>

void PhysicsEngine::ProcessSpritePhysics(double deltaTime)
{
    for (Sprite* sprite : _sprites)
    {
        if (!sprite->enablePhysics) continue;

        sprite->_forcesAccumulated.y += _gravityAcceleration * sprite->_mass * sprite->gravityMultiplier;

        Vector2 acceleration = sprite->_forcesAccumulated * (1.0f/sprite->_mass);
        sprite->_velocity += acceleration * deltaTime;
        sprite->_rect.position += sprite->_velocity * deltaTime;
        sprite->_forcesAccumulated = 0;
    }
}