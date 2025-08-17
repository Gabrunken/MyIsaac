#pragma once
#include <Game States/game_state_base.hpp>
#include <iostream>

class MainMenuGameState : public GameStateBase
{
public:
	static constexpr inline MainMenuGameState& GetInstance() noexcept
	{
		static MainMenuGameState instance;
		return instance;
	}

protected:
	virtual bool Initialize() override;
	virtual EventHandlingResult HandleEvents(const SDL_Event& event) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(SDL_Renderer* const renderer, SDL_Window* const window) override;
	virtual void Terminate() override;
};