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
	    &_atlasRect.GetSDLFRect(),
	    &_rect.GetSDLFRect());
    else
        SDL_RenderTextureRotated(
        const_cast<SDL_Renderer*>(SSGE::GetRenderer()),
        texture,
        &_atlasRect.GetSDLFRect(),
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

void Sprite::SetScale(Vector2 scale) noexcept
{
    Vector2 renderBounds = SSGE::GetRenderBounds();
    //Also take into account the atlas rect and not the whole texture size
    _rect.size.x = (_atlasRect.size.x / renderBounds.x) * scale.x;
    _rect.size.y = (_atlasRect.size.y / renderBounds.x) * scale.y;
}