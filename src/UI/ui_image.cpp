#include <UI/ui_image.hpp>
#include <application.hpp>

void UIImage::DrawSelf()
{
	SDL_Texture* texture = _texture.get();
	if (!texture) return;
	SDL_RenderTexture(IsaacClone::isaacRenderer, texture, nullptr, &_absoluteRect.GetSDLFRect());
}

void UIImage::SetScaleRelativeToTexture(float size) noexcept
{
	SDL_Texture* texture = _texture.get();
	if (!texture)
	{
		std::printf("Cannot adapt a UIImage scale to its texture size because no texture was set.");
		return;
	}

	_absoluteRect.size.x = texture->w / IsaacClone::windowScaledSize.x * size;
	_absoluteRect.size.y = texture->h / IsaacClone::windowScaledSize.x * size;
}