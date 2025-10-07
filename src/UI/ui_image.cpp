#include <UI/ui_image.hpp>
#include <engine.hpp>

void UIImage::DrawSelf()
{
	SDL_Texture* texture = _texture.get();
	if (!texture) return;
	SDL_RenderTexture(const_cast<SDL_Renderer*>(SSGE::GetRenderer()), texture, nullptr, &_absoluteRect.GetSDLFRect());
}

void UIImage::SetScaleRelativeToTexture(float size) noexcept
{
	SDL_Texture* texture = _texture.get();
	if (!texture)
	{
		std::printf("Cannot adapt a UIImage scale to its texture size because no texture was set.");
		return;
	}

	Vector2 renderBounds = SSGE::GetRenderBounds();
	_absoluteRect.size.x = texture->w / renderBounds.x * size;
	_absoluteRect.size.y = texture->h / renderBounds.x * size;
}