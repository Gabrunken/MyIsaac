#pragma once
#include <vector2.hpp>
#include <SDL3/SDL.h>

class Rect
{
public:
	Rect() {}
	Rect(const Vector2& position, const Vector2& size) : position(position), size(size) {}
	Rect(const SDL_FRect& rect) : position(rect.x, rect.y), size(rect.w, rect.h) {}
	Rect(const SDL_Rect& rect) : position(static_cast<float>(rect.x), static_cast<float>(rect.y)),
								 size(static_cast<float>(rect.w), static_cast<float>(rect.h)) {}

	bool inline IsPointInsideRect(const Vector2& point) const noexcept
	{
		if (point.x > position.x && point.y > position.y)
		{
			if (point.x < position.x + size.x && point.y < position.y + size.y)
				return true;
		}

		return false;
	}

	operator SDL_FRect() const
	{
		return { position.x, position.y, size.x, size.y };
	}

	operator SDL_Rect() const
	{
		return { static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y) };
	}

	const inline SDL_FRect& GetSDLFRect() const
	{
		_sdlFRect.x = position.x;
		_sdlFRect.y = position.y;
		_sdlFRect.w = size.x;
		_sdlFRect.h = size.y;

		return _sdlFRect;
	}

	Vector2 position, size = Vector2(1);

protected:
	mutable SDL_FRect _sdlFRect;
};