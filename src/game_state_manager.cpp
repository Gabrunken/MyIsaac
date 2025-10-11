#include <game_state_manager.hpp>
#include <physics_engine.hpp>
#include <iostream>

bool GameStateManager::Update() noexcept
{
	if (quitCurrentState) { quitCurrentState = false;  return false; }
	if (!gameState.get()) return false;

	bool result = false;


	if (lastTime == 0) lastTime = SDL_GetTicks(); //This game state just started, first frame deltaTime will be 0.

	uint64_t deltaTime = (SDL_GetTicks() - lastTime);
	if (gameState->_updateDelay > deltaTime)
	{
		SDL_Delay((gameState->_updateDelay - deltaTime)); //Freezes the thread to synchronize the current frame rate with the desired one.
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

	//Update physics
	static double physicsTimeAccumulator; //How much time since the last physics update
	physicsTimeAccumulator += deltaTime;

	if (gameState->_physicsUpdateDelay <= physicsTimeAccumulator)
	{
		double physicsDeltaTime = gameState->_physicsUpdateDelay / 1000.0;
		gameState->PhysicsUpdate(physicsDeltaTime);
		PhysicsEngine::ProcessSpritePhysics(physicsDeltaTime);
		physicsTimeAccumulator -= gameState->_physicsUpdateDelay;
	}

	//The rendering and the physics do not execute at the same pace so on screen,
	//physics object might appear moving with stutter. To fix this i use this interpolation factor
	//Which tells how much should we move from the previous renderer state to the current.
	//TODO: implement interpolation, it is not easy so i'll finish the actual physics update first.
	double interpolationFactor = physicsTimeAccumulator / gameState->_physicsUpdateDelay;

	//Update logic
	gameState->Update(deltaTime / 1000.0f);

	gameState->Render();

	return result;
}

void GameStateManager::FreeState() noexcept
{
	if (!gameState) return;
	gameState.reset();
}
