#pragma once
#include <Game States/game_state_base.hpp>

class GameStateManager
{
public:
	GameStateManager() = delete;
	GameStateManager(const GameStateManager& other) = delete;
	void operator=(const GameStateManager& other) = delete;

	static void Initialize(SDL_Renderer& rendererRef, SDL_Window& windowRef, GameStateBase& initialGameState) noexcept;
	static bool SetState(GameStateBase& newGameState) noexcept;
	static bool Update() noexcept;
	static void Terminate() noexcept;

private:
	static inline GameStateBase* gameState;

	static inline SDL_Event event;
	static inline float lastTime;

	static inline SDL_Renderer* renderer;
	static inline SDL_Window* window;

	static inline bool hasBeenInitialized = false;
};