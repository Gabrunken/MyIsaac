#include <UI/ui_button.hpp>
#include <Math/rect.hpp>

void UIButton::CheckForHover()  noexcept
{
	if (!_enabled) return;
	if (!_onHoverBeginCallback && !_onHoverEndCallback) return;

	Vector2 mousePos = SSGE::GetMousePosition();

	if (_absoluteRect.IsPointInsideRect(mousePos))
	{
		if (!_isHovered)
		{
			_isHovered = true;
			if (_onHoverBeginCallback) _onHoverBeginCallback();
		}
	}

	else if (_isHovered)
	{
		_isHovered = false;
		if (_onHoverEndCallback) _onHoverEndCallback();
	}
}

void UIButton::CheckForClick(bool mouseDown) noexcept
{
	if (!_onClickCallback || !_enabled) return;

	Vector2 mousePos = SSGE::GetMousePosition();

	if (_absoluteRect.IsPointInsideRect(mousePos))
	{
		if (_mouseDownOnIt && !mouseDown)
		{
			_onClickCallback();
			_mouseDownOnIt = false;
			return;
		}

		else if (mouseDown)
			_mouseDownOnIt = true;
	}
}