#pragma once
#include <SDL3/SDL.h>
#include <vector2.hpp>
#include <string>
#include <game_state_base.hpp>
#include <game_state_manager.hpp>
#include <resource_manager.hpp>

namespace SSGE
{
	static bool SSGEStarted = false;
	inline static SDL_Renderer* renderer;
	inline static SDL_Window* window;
	inline static Vector2 renderBounds;

	inline const SDL_Renderer* GetRenderer() noexcept {return renderer;}
	inline const SDL_Window* GetWindow() noexcept {return window;}
	inline Vector2 GetRenderBounds() noexcept {return renderBounds;}

	template<typename T>
	bool Init(const std::string& windowTitle, Vector2 windowSize, Vector2 renderBounds) noexcept
	{
		static_assert(std::is_base_of<GameStateBase, T>());

		if (SSGEStarted) return true;
		SSGEStarted = true;

		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			std::printf("SSGE: Couldn't initialize SDL: %s\n", SDL_GetError());
			return false;
		}

		//SDL_Rect displayRect;
		//SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &displayRect);

		//Vector2 windowSize;

		//windowSize.x = displayRect.w / static_cast<float>(2);
		//windowSize.y = displayRect.h / static_cast<float>(2);

		if (!SDL_CreateWindowAndRenderer(windowTitle.c_str(), windowSize.x, windowSize.y, 0, &window, &renderer))
		{
			std::printf("SSGE: Couldn't create the window: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderScale(renderer, windowSize.x / renderBounds.x, windowSize.y / renderBounds.y);

		ResourceManager::GetInstance().Initialize();
		GameStateManager::SetState(std::make_unique<T>());

		return true;
	}

	bool Update() noexcept;
	void Terminate() noexcept;

	const SDL_Renderer* GetRenderer() noexcept;
	const SDL_Window* GetWindow() noexcept;
}