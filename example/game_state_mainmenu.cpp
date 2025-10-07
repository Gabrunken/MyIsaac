#include <Game States/game_state_mainmenu.hpp>
#include <game_state_manager.hpp>
#include <resource_manager.hpp>
#include <engine.hpp>
#include <UI/ui_button.hpp>

void QuitButtonCallback();

MainMenuGameState::MainMenuGameState()
{
	std::printf("Initializing main menu\n");

	_backgroundImage = UIImage({ {0, 0}, {1, 1} }, nullptr, Vector2(-1.0f));
	_backgroundImage.SetTexture(ResourceManager::GetInstance().LoadResource<SDL_Texture>("textures\\mainmenu_background.jpg", SDL_SCALEMODE_LINEAR));

	_buttonsPanel = UIElement({ {0.05f, 0.10f}, {0.35f, 0.8f} }, nullptr, Vector2(-1.0f));

	_quitButton = UIButton({ {0, 0}, {1, 1} }, &_buttonsPanel, Vector2(0.0f, -1.0f));
	_quitButton.SetTexture(ResourceManager::GetInstance().LoadResource<SDL_Texture>("textures\\button.png", SDL_SCALEMODE_NEAREST));
	_quitButton.SetScaleRelativeToTexture(0.5f);
	_quitButton.CenterPositionX();
	_quitButton.SetOnClickCallback(QuitButtonCallback);
}

EventHandlingResult MainMenuGameState::HandleEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_EVENT_QUIT:
		return EventHandlingResult::TerminateApplication;

	case SDL_EVENT_KEY_DOWN:
		switch (event.key.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return EventHandlingResult::TerminateApplication;
		default:
			break;
		}
		break;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		if (event.button.button == 1)
		{
			_quitButton.CheckForClick(true);
		}

		break;

	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (event.button.button == 1)
		{
			_quitButton.CheckForClick(false);
		}

		break;

	default:
		return EventHandlingResult::Continue;
	}

	return EventHandlingResult::Continue;
}

void MainMenuGameState::Update(float deltaTime)
{

}

void MainMenuGameState::Render()
{
	SDL_RenderClear(IsaacClone::isaacRenderer);
	_backgroundImage.DrawSelf();
	_quitButton.DrawSelf();
	SDL_RenderPresent(IsaacClone::isaacRenderer);
}

MainMenuGameState::~MainMenuGameState()
{
	std::printf("Exiting main menu\n");
}

void QuitButtonCallback()
{
	GameStateManager::QueueQuitState();
}