#include <UI/ui_element.hpp>
#include <engine.hpp>

void UIElement::SetRelativePosition(const Vector2& position) noexcept
{
	Rect parentRect{};

	if (_parent)
	{
		parentRect.position.x = _parent->_absoluteRect.position.x;
		parentRect.position.y = _parent->_absoluteRect.position.y;
		parentRect.size.x = _parent->_absoluteRect.size.x;
		parentRect.size.y = _parent->_absoluteRect.size.y;
	}

	else
	{
		Vector2 renderBounds = SSGE::GetRenderBounds();
		parentRect.size.x = renderBounds.x;
		parentRect.size.y = renderBounds.y;
	}

	Vector2 adjustedAnchor = (_anchor + 1.0f) / 2.0f;
	Vector2 relativePosition = {
		parentRect.position.x + parentRect.size.x * adjustedAnchor.x + position.x * parentRect.size.x,
		parentRect.position.y + parentRect.size.y * adjustedAnchor.y + position.y * parentRect.size.y };

	_absoluteRect.position.x = relativePosition.x;
	_absoluteRect.position.y = relativePosition.y;
}

void UIElement::SetRelativeSize(const Vector2& size) noexcept
{
	Vector2 parentSize;

	if (_parent)
	{
		parentSize.x = _parent->_absoluteRect.size.x;
		parentSize.y = _parent->_absoluteRect.size.y;
	}

	else
	{
		Vector2 renderBounds = SSGE::GetRenderBounds();
		parentSize.x = renderBounds.x;
		parentSize.y = renderBounds.y;
	}

	Vector2 relativeSize = {
		size.x * parentSize.x,
		size.y * parentSize.y
		};

	_absoluteRect.size.x = relativeSize.x;
	_absoluteRect.size.y = relativeSize.y;
}

void UIElement::SetRelativeRect(const Rect& rect) noexcept
{
	SetRelativePosition({ rect.position.x, rect.position.y });
	SetRelativeSize({ rect.size.x, rect.size.y });
}