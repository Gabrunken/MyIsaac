#include <engine.hpp>
#include <vector2.hpp>
#include <iostream>
#include <game_state_manager.hpp>
#include <cstdlib>

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