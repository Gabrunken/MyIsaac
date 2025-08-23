#pragma once
#include <UI/ui_image.hpp>

typedef void (*OnClickCallback)(void);
typedef void (*OnHoverBeginCallback)(void);
typedef void (*OnHoverEndCallback)(void);

class UIButton : public UIImage
{
public:
	using UIImage::UIImage;

	void CheckForHover() noexcept; //Should be called on each frame.
	void CheckForClick(bool mouseDown) noexcept; //Should be called on mouse down AND mouse up event.
	void SetOnClickCallback(OnClickCallback callback) noexcept { if (callback) _onClickCallback = callback; };
	void SetOnHoverBeginCallback(OnHoverBeginCallback callback) noexcept { if (callback) _onHoverBeginCallback = callback; };
	void SetOnHoverEndCallback(OnHoverEndCallback callback) noexcept { if (callback) _onHoverEndCallback = callback; };

	void inline SetEnabled(bool value) noexcept { _enabled = value; }

protected:
	bool _mouseDownOnIt = false; //If the mouse down event was fired upon this button, set this to true.
	bool _isHovered = false;

	bool _enabled = true;

	OnClickCallback _onClickCallback = nullptr;
	OnHoverBeginCallback _onHoverBeginCallback = nullptr;
	OnHoverEndCallback _onHoverEndCallback = nullptr;
};