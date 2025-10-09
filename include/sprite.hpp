#pragma once
#include <memory>
#include <Math/rect.hpp>
#include <string>
#include <ssge.hpp>

class Sprite
{
public:
    Sprite(const std::string& texturePath, Rect atlasRect, SDL_ScaleMode scaleMode)
     : _texturePtr(ResourceManager::GetInstance().LoadResource<SDL_Texture>(texturePath, scaleMode)),
       _atlasRect(atlasRect)
    {
        //Set rect size based on texture size
        SetScale(Vector2(1.0f)); //Doing this works too, i prevent code redundancy
    }

    void Rotate(float amount) noexcept; //rotate by amount
    inline void SetRotation(float rotation) noexcept {_rotation = std::clamp(rotation, 0.0f, 360.0f);} //set a new rotation discarding the previous one

    inline void Move(Vector2 amount) noexcept {_rect.position += amount;} //move by amount
    inline void SetPosition(Vector2 position) noexcept {_rect.position = position;} //set a new position discarding the previous one

    void SetScale(Vector2 scale) noexcept; //Sets the scale inside _rect, based also on texture size

    void DrawSelf() const noexcept;

private:
    std::shared_ptr<SDL_Texture> _texturePtr = nullptr;
    Rect _rect = {};
    float _rotation = 0.0f;

    //The rect inside the texture atlas. If the texture contains only 1 sprite, then make this the size of the whole texture and position 0.
    //Like this the user should know the exact size and position of its sprite in the atlas, but at least by using a rect instead of Vector2 indices
    //He can load sprites which have rectangular shapes or are in different positions inside the atlas.
    //So this is in actual pixels.
    Rect _atlasRect;
};