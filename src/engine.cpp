#include <engine.hpp>
#include <vector2.hpp>
#include <iostream>
#include <game_state_manager.hpp>
#include <cstdlib>

Vector2 SSGE::GetMousePosition() noexcept
{
	Vector2 mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(const_cast<SDL_Window*>(SSGE::GetWindow()), &windowSizeX, &windowSizeY);

	mousePos.x /= windowSizeX;
	mousePos.y /= windowSizeY;

	Vector2 renderBounds = SSGE::GetRenderBounds();
	mousePos.x *= renderBounds.x;
	mousePos.y *= renderBounds.y;

	return mousePos;
}

bool SSGE::Update() noexcept
{
	return GameStateManager::Update();
}

void SSGE::Terminate() noexcept
{
	if (!SSGEStarted) return;

	GameStateManager::FreeState();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}