#include <application.hpp>
#include <vector2.hpp>
#include <iostream>
#include <game_state_manager.hpp>
#include <Game States/game_state_mainmenu.hpp>
#include <cstdlib>

static void Update();
static void Terminate();

void IsaacClone::Start()
{
	std::atexit(Terminate);

	std::printf("Starting Isaac Clone...\n");

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		std::exit(1);
	}

	SDL_Rect displayRect;
	SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &displayRect);

	Vector2 windowSize;

	windowSize.x = displayRect.w / 2;
	windowSize.y = displayRect.h / 2;

	SDL_Window* window;
	SDL_Renderer* renderer;

	constexpr Vector2 coordinateBounds(16.0f, 9.0f);

	if (!SDL_CreateWindowAndRenderer("Isaac Clone", windowSize.x, windowSize.y, 0, &window, &renderer))
	{
		std::printf("Couldn't create the window: %s\n", SDL_GetError());
		std::exit(1);
	}

	SDL_SetRenderScale(renderer, windowSize.x / coordinateBounds.x, windowSize.y / coordinateBounds.y);

	GameStateManager::Initialize(*renderer, *window, MainMenuGameState::GetInstance());

	Update();
}

static void Update()
{
	while (GameStateManager::Update());
	Terminate();
}

static void Terminate()
{
	GameStateManager::Terminate();
	SDL_Quit();
}