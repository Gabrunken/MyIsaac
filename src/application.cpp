#include <application.hpp>
#include <vector2.hpp>
#include <iostream>
#include <game_state_manager.hpp>
#include <Game States/game_state_mainmenu.hpp>
#include <cstdlib>
#include <resource_manager.hpp>

static void Update();
static void Terminate();

SDL_Renderer* isaacRenderer;
SDL_Window* isaacWindow;
Vector2 windowScaledSize;

static bool isaacStarted = false;

void IsaacClone::Start()
{
	if (isaacStarted) return;
	isaacStarted = true;

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

	windowSize.x = displayRect.w / static_cast<float>(2);
	windowSize.y = displayRect.h / static_cast<float>(2);

	if (!SDL_CreateWindowAndRenderer("Isaac Clone", windowSize.x, windowSize.y, 0, &isaacWindow, &isaacRenderer))
	{
		std::printf("Couldn't create the window: %s\n", SDL_GetError());
		std::exit(1);
	}

	SDL_SetRenderScale(isaacRenderer, windowSize.x / windowScaledSize.x, windowSize.y / windowScaledSize.y);

	ResourceManager::GetInstance().Initialize();
	GameStateManager::SetState(std::make_unique<MainMenuGameState>());

	Update();
}

static void Update()
{
	while (GameStateManager::Update());
	Terminate();
}

static void Terminate()
{
	GameStateManager::FreeState();
	SDL_DestroyWindow(IsaacClone::isaacWindow);
	SDL_DestroyRenderer(IsaacClone::isaacRenderer);
	SDL_Quit();
}