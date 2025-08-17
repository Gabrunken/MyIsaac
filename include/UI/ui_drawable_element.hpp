#pragma once
#include <UI/ui_element.hpp>

class UIDrawableElement : public UIElement
{
public:
	virtual void DrawSelf() = 0;
};