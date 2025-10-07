#pragma once
#include <SDL3/SDL.h>
#include <vector2.hpp>
#include <algorithm>
#include <Math/rect.hpp>

class UIElement
{
public:
	UIElement() noexcept {}

	UIElement(const Rect& rect) noexcept { SetRelativeRect(rect); }

	UIElement(
		const Rect& rect,
		UIElement* parent) noexcept :
		_parent(parent)
	{ SetRelativeRect(rect); }

	UIElement(
		const Rect& rect,
		UIElement* parent,
		const Vector2& anchor) noexcept :
		_parent(parent),
		_anchor(std::clamp(anchor.x, -1.0f, 1.0f), std::clamp(anchor.y, -1.0f, 1.0f))
	{ SetRelativeRect(rect); }

	void SetRelativePosition(const Vector2& position) noexcept;
	constexpr inline void SetAbsolutePosition(const Vector2& position) noexcept
	{
		_absoluteRect.position.x = position.x;
		_absoluteRect.position.y = position.y;
	}

	void SetRelativeSize(const Vector2& size) noexcept;
	constexpr inline void SetAbsoluteSize(const Vector2& size) noexcept
	{
		_absoluteRect.size.x = size.x;
		_absoluteRect.size.y = size.y;
	}

	void SetRelativeRect(const Rect& rect) noexcept;
	constexpr inline void SetAbsoluteRect(const Rect& rect) noexcept
	{
		_absoluteRect = rect;
	}

	void inline SetAnchor(const Vector2& anchor) noexcept
	{
		_anchor = anchor.GetNormalized();
	}

	void inline CenterPosition() noexcept
	{
		_absoluteRect.position.x -= _absoluteRect.size.x / 2.0f;
		_absoluteRect.position.y -= _absoluteRect.size.y / 2.0f;
	}

	void inline CenterPositionX() noexcept
	{
		_absoluteRect.position.x -= _absoluteRect.size.x / 2.0f;
	}

	void inline CenterPositionY() noexcept
	{
		_absoluteRect.position.y -= _absoluteRect.size.y / 2.0f;
	}

protected:
	Rect _absoluteRect{};
	UIElement* _parent = nullptr; //If it is null, just treat it as the window's rect.
	Vector2 _anchor{};
};