#pragma once
#include <memory>
#include <string>
#include <Math/rect.hpp>
#include <vector2.hpp>
#include <SDL3/SDL.h>

class Sprite;

enum class CollisionType
{
    None,
    Rect,
    Circle
};

typedef void (*OnCollisionEnterCallback)(const Sprite& other);
typedef void (*OnCollisionExitCallback)(const Sprite& other);

class Sprite
{
public:
    Sprite(const std::string& texturePath, Rect atlasRect, SDL_ScaleMode scaleMode);
    ~Sprite();

    inline void SetRotation(float rotation) noexcept {_rotation = std::clamp(rotation, 0.0f, 360.0f);} //set a new rotation discarding the previous one
    void Rotate(float amount) noexcept; //rotate by amount
    inline float GetRotation() const noexcept {return _rotation;}

    inline void Move(Vector2 amount) noexcept {_rect.position += amount;} //move by amount
    inline void SetPosition(Vector2 position) noexcept {_rect.position = position;} //set a new position discarding the previous one
    inline void SetPositionCentered(Vector2 position) noexcept {_rect.position = position + _rect.size / 2.0f;}
    inline Vector2 GetPosition() const noexcept {return _rect.position;}
    inline Vector2 GetPositionCentered() const noexcept {return _rect.position + _rect.size / 2.0f;}

    void SetScale(Vector2 scale) noexcept; //Sets the scale inside _rect, based also on texture size
    inline Vector2 GetScale() const noexcept {return _rect.size;}

    void DrawSelf() const noexcept;

    inline void SetMass(float mass) noexcept {if (mass <= 0.001f) {_mass = 0.001f; return;} _mass = mass;}
    inline float GetMass() const noexcept {return _mass;}
    inline float GetInverseMass() const noexcept {if (_mass < 0.001f) return 0.0f; return 1.0f/_mass;}

    inline void SetOnCollisionEnterCallback(OnCollisionEnterCallback func) noexcept
    {
        if (func)
            _onCollisionEnterCallback = func;
    }

    inline void SetOnCollisionExitCallback(OnCollisionExitCallback func) noexcept
    {
        if (func)
            _onCollisionExitCallback = func;
    }

    inline void SetCollisionType(CollisionType type) noexcept {_collisionType = type;}

    bool enablePhysics = true;
    float gravityMultiplier = 1.0f;

private:
    friend class PhysicsEngine;

    std::shared_ptr<SDL_Texture> _texturePtr = nullptr;
    Rect _rect = {}; //Position and size in world coordinates
    float _rotation = 0.0f;

    float _mass = 1.0f; //mass is not weight, the weight is based on the gravity
    Vector2 _velocity;
    Vector2 _forcesAccumulated; //The various forces applied in a single frame to this object

    CollisionType _collisionType = CollisionType::Rect;
    bool _isTrigger = false; //Is this body a trigger or an obstacle?
    bool _isColliding = false; //Are we currently inside an object?
    bool _isStatic = false; //Does it move on collision?
    unsigned int _collisionCount = 0; //How many bodies is this one colliding with at the current frame.

    OnCollisionEnterCallback _onCollisionEnterCallback = nullptr;
    OnCollisionExitCallback _onCollisionExitCallback = nullptr; //This will only be called if this collision or the other collision is a trigger.

    //The rect inside the texture atlas. If the texture contains only 1 sprite, then make this the size of the whole texture and position 0.
    //Like this the user should know the exact size and position of its sprite in the atlas, but at least by using a rect instead of Vector2 indices
    //He can load sprites which have rectangular shapes or are in different positions inside the atlas.
    //So this is in actual pixels.
    Rect _atlasRect;
};
