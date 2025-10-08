#pragma once
#include <memory>
#include <Math/rect.hpp>
#include <string>
#include <ssge.hpp>

class Sprite
{
public:
    Sprite(const std::string& texturePath, SDL_ScaleMode scaleMode)
     : _texturePtr(ResourceManager::GetInstance().LoadResource<SDL_Texture>(texturePath, scaleMode))
    {
        //Set rect size based on texture size
        SetScale(Vector2(1.0f)); //Doing this works too, i prevent code redundancy
    }

    void Rotate(float amount) noexcept; //rotate by amount
    void SetRotation(float rotation) noexcept; //set a new rotation discarding the previous one

    void SetScale(Vector2 scale) noexcept; //Sets the scale inside _rect, based also on texture size

    void DrawSelf() const noexcept;

private:
    std::shared_ptr<SDL_Texture> _texturePtr = nullptr;
    Rect _rect = {};
    float _rotation = 0.0f;
};