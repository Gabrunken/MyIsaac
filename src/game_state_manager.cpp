#include <game_state_manager.hpp>
#include <iostream>

void GameStateManager::Initialize(SDL_Renderer& rendererRef, SDL_Window& windowRef, GameStateBase& initialGameState) noexcept
{
	if (hasBeenInitialized) return;

	renderer = &rendererRef;
	window = &windowRef;
	if (!SetState(initialGameState))
		return;

	hasBeenInitialized = true;
}

bool GameStateManager::SetState(GameStateBase& newGameState) noexcept
{
	if (gameState)
		gameState->Terminate();

	gameState = &newGameState;

	if (!gameState->Initialize())
	{
		std::printf("GameStateManager Error: failed to initialize the passed game state.\n");
		return false;
	}

	return true;
}

bool GameStateManager::Update() noexcept
{
	bool result = false;

	if (!hasBeenInitialized)
	{
		std::printf("GameStateManager Error: you must initialize this class before calling the update function.\n");
		return result;
	}

	if (!gameState->hasBeenInitialized)
	{
		std::printf("GameStateManager Error: the selected game state must be always initialized before running its update function.\n");
		return result;
	}

	SDL_PollEvent(&event);
	EventHandlingResult eventResult = gameState->HandleEvents(event);
	switch (eventResult)
	{
	case EventHandlingResult::TerminateApplication:
		result = false;
		gameState->Terminate();
		break;
	case EventHandlingResult::Continue:
		result = true;
		break;
	default:
		result = true;
		break;
	}

	gameState->Update(0.018f);
	gameState->Render(renderer, window);

	return result;
}

void GameStateManager::Terminate() noexcept
{
	if (!hasBeenInitialized) return;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	hasBeenInitialized = false;
}