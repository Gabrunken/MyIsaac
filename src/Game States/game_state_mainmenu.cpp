#include <Game States/game_state_mainmenu.hpp>

bool MainMenuGameState::Initialize()
{
	if (hasBeenInitialized) return hasBeenInitialized;

	std::printf("Initializing main menu\n");

	hasBeenInitialized = true;
	return hasBeenInitialized;
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
	default:
		return EventHandlingResult::Continue;
	}
}

void MainMenuGameState::Update(float deltaTime)
{

}

void MainMenuGameState::Render(SDL_Renderer* const renderer, SDL_Window* const window)
{
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void MainMenuGameState::Terminate()
{
	if (!hasBeenInitialized) return;

	std::printf("Exiting main menu\n");
	hasBeenInitialized = false;
}