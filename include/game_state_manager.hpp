#pragma once
#include <Game States/game_state_base.hpp>
#include <memory>

class GameStateManager
{
public:
	GameStateManager() = delete;
	GameStateManager(const GameStateManager& other) = delete;
	void operator=(const GameStateManager& other) = delete;

	static void SetState(std::unique_ptr<GameStateBase> newGameState) noexcept;
	static bool Update() noexcept;
	static void FreeState() noexcept; //Must be called only outside the current state.

	//Should be called internally by states to quit the application.
	//It is needed since exiting using the std::exit() function crashes the process. DONT ASK WHY.
	static inline void QueueQuitState() noexcept { quitCurrentState = true; }

private:
	static inline std::unique_ptr<GameStateBase> gameState;

	static inline SDL_Event event;
	static inline uint64_t lastTime;

	static inline bool quitCurrentState; //Used internally by states to queue a quit action without passing by the event loop.
};