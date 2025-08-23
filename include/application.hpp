#pragma once
#include <SDL3/SDL.h>
#include <vector2.hpp>

namespace IsaacClone
{
	inline extern SDL_Renderer* isaacRenderer = nullptr;
	inline extern SDL_Window* isaacWindow = nullptr;
	inline extern Vector2 windowScaledSize = Vector2(16.0f, 9.0f);

	void Start();
}