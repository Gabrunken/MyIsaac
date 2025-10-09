#include <game_state_manager.hpp>
#include <iostream>

bool GameStateManager::Update() noexcept
{
	if (quitCurrentState) { quitCurrentState = false;  return false; }
	if (!gameState.get()) return false;

	bool result = false;

	if (lastTime == 0) SDL_GetTicks();

	uint64_t deltaTime = (SDL_GetTicks() - lastTime);
	if (gameState->_updateDelay > deltaTime)
	{
		SDL_Delay((gameState->_updateDelay - deltaTime));
		deltaTime = SDL_GetTicks() - lastTime;
	}

	lastTime = SDL_GetTicks();

	SDL_PollEvent(&event);
	EventHandlingResult eventResult = gameState->HandleEvents(event);
	switch (eventResult)
	{
	case EventHandlingResult::TerminateApplication:
		result = false;
		break;
	case EventHandlingResult::Continue:
		result = true;
		break;
	default:
		result = true;
		break;
	}

	gameState->Update(deltaTime / 1000.0f);
	gameState->Render();

	return result;
}

void GameStateManager::FreeState() noexcept
{
	if (!gameState) return;
	gameState.reset();
}