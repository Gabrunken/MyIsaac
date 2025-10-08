#include <sprite.hpp>
#include <cmath>
#include <algorithm>

void Sprite::DrawSelf() const noexcept
{
	SDL_Texture* texture = _texturePtr.get();
	if (!texture) return;
	if (std::fabs(_rotation) < 1e-5f)
	    SDL_RenderTexture(
	    const_cast<SDL_Renderer*>(SSGE::GetRenderer()),
	    texture,
	    nullptr,
	    &_rect.GetSDLFRect());
    else
        SDL_RenderTextureRotated(
        const_cast<SDL_Renderer*>(SSGE::GetRenderer()),
        texture,
        nullptr,
        &_rect.GetSDLFRect(),
        _rotation,
        nullptr,
        SDL_FLIP_NONE
        );
}

void Sprite::Rotate(float amount) noexcept
{
    if (amount > 360.0f) {std::printf("Cannot rotate more than 360° at a time\n"); return;}

    if (_rotation + amount > 360.0f)
    {
        _rotation = _rotation + amount - 360.0f;
        return;
    }

    _rotation += amount;
}

void Sprite::SetRotation(float rotation) noexcept
{
    _rotation = std::clamp(rotation, 0.0f, 360.0f);
}

void Sprite::SetScale(Vector2 scale) noexcept
{
    SDL_Texture* texture = _texturePtr.get();
    if (!texture) {std::printf("A texture pointer has been found invalid when rescaling a sprite\n"); return;};
    Vector2 renderBounds = SSGE::GetRenderBounds();
    _rect.size.x = (texture->w / renderBounds.x) * scale.x;
    _rect.size.y = (texture->h / renderBounds.x) * scale.y;
}