#pragma once
#include <vector>
#include <vector2.hpp>
#include <sprite.hpp>

class PhysicsEngine
{
public:
    PhysicsEngine();
    ~PhysicsEngine();

    static inline void AddSprite(Sprite* sprite) {_sprites.push_back(sprite);}
    static inline bool RemoveSprite(Sprite* sprite)
    {
        auto it = std::find(_sprites.begin(), _sprites.end(), sprite);
        if (it == _sprites.end()) return false;
        _sprites.erase(it);
        return true;
    }

    static inline void AddForce(Sprite& sprite, Vector2 force)
    {
        sprite._forcesAccumulated += force;
    }

    static inline void AddImpulse(Sprite& sprite, Vector2 impulse)
    {
        sprite._velocity += impulse * (1.0f/sprite._mass); //I should add an inverseMass member to optimize.
    }

private:
    friend class GameStateManager;

    //Update the sprites' state based on their accumulated forces.
    static void ProcessSpritePhysics(double deltaTime);
    static inline std::vector<Sprite*> _sprites;

	static inline float _gravityAcceleration = 9.81f;
};