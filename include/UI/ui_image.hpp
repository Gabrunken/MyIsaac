#pragma once
#include <UI/ui_drawable_element.hpp>
#include <resource_manager.hpp>
#include <engine.hpp>

class UIImage : public UIDrawableElement
{
public:
	using UIDrawableElement::UIDrawableElement;

	void inline SetTexture(std::shared_ptr<SDL_Texture> texture) noexcept
	{
		if (!texture) return;
		_texture = texture;
	}

	void SetScaleRelativeToTexture(float size) noexcept;

	virtual void DrawSelf() override;

protected:
	std::shared_ptr<SDL_Texture> _texture = nullptr;
};