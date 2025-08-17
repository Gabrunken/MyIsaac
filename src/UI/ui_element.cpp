#include <UI/ui_element.hpp>

void UIElement::SetRelativePosition(const Vector2& position) noexcept
{
	if (!window || !renderer) return;

	SDL_Rect parentRect{};

	if (_parent)
	{
		parentRect.x = _parent->_absoluteRect.x;
		parentRect.y = _parent->_absoluteRect.y;
		parentRect.w = _parent->_absoluteRect.w;
		parentRect.h = _parent->_absoluteRect.h;
	}

	else
	{
		SDL_GetWindowSize(window, &parentRect.w, &parentRect.h);
		Vector2 renderScale;
		SDL_GetRenderScale(renderer, &renderScale.x, &renderScale.y);

		parentRect.w /= renderScale.x;
		parentRect.h /= renderScale.y;
	}

	absoluteRect.x = 
}