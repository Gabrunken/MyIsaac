#pragma once
#include <Game States/game_state_base.hpp>
#include <iostream>
#include <UI/ui_button.hpp>

class MainMenuGameState : public GameStateBase
{
public:
	MainMenuGameState();
	~MainMenuGameState();

protected:
	virtual EventHandlingResult HandleEvents(const SDL_Event& event) override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	UIButton _quitButton;
	UIImage _backgroundImage;
	UIElement _buttonsPanel;
};