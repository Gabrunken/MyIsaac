#pragma once
#include <SDL3/SDL.h>
#include <vector2.hpp>

class UIElement
{
public:
	static constexpr inline void Initialize(
		SDL_Window& windowRef,
		SDL_Renderer& rendererRef) noexcept
	{
		window = &windowRef;
		renderer = &rendererRef;
	}

	constexpr UIElement(const SDL_FRect& rect) noexcept : _absoluteRect(rect) {}
	
	constexpr UIElement(
		const SDL_FRect& rect, 
		UIElement* parent) noexcept : 
		_absoluteRect(rect), 
		_parent(parent) {}

	constexpr UIElement(
		const SDL_FRect& rect, 
		UIElement* parent,
		const Vector2& anchor) noexcept : 
		_absoluteRect(rect), 
		_parent(parent),
		_anchor(anchor.GetNormalized()) {}

	void SetRelativePosition(const Vector2& position) noexcept;
	constexpr inline void SetAbsolutePosition(const Vector2& position) noexcept
	{
		_absoluteRect.x = position.x;
		_absoluteRect.y = position.y;
	}

	void SetRelativeSize(const Vector2& size) noexcept;
	constexpr inline void SetAbsoluteSize(const Vector2& size) noexcept
	{
		_absoluteRect.w = size.x;
		_absoluteRect.h = size.y;
	}

	void SetRelativeRect(const SDL_FRect& rect) noexcept;
	constexpr inline void SetAbsoluteRect(const SDL_FRect& rect) noexcept
	{
		_absoluteRect = rect;
	}

	void inline SetAnchor(const Vector2& anchor) noexcept
	{
		_anchor = anchor.GetNormalized();
	}

protected:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	SDL_FRect _absoluteRect{};
	UIElement* _parent = nullptr; //If it is null, just treat it as the window's rect.
	Vector2 _anchor{};
};