#pragma once
#include <SDL3/SDL.h>

enum class EventHandlingResult
{
	TerminateApplication,
	Continue
};

typedef void (*UpdateCallback) (float deltaTime);
typedef EventHandlingResult (*HandleEventsCallback) (SDL_Event& event);

class GameStateBase
{
public:
	GameStateBase(const GameStateBase& other) = delete;
	void operator=(const GameStateBase& other) = delete;

protected:
	constexpr GameStateBase() noexcept = default;

protected:

	/*
	* Here you should initialize every resource you'll use in the other methods.
	*/
	virtual bool Initialize() = 0;

	/*
	* Any save upon close logic should be written inside this function, since when you return TerminateApplication it does not pass its last execution to Update.
	*/
	virtual EventHandlingResult HandleEvents(const SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* const renderer, SDL_Window* const window) = 0;

	/*
	* Every resource initialized in "Initialize" must be freed here.
	*/
	virtual void Terminate() = 0;

	friend class GameStateManager;

	static inline bool hasBeenInitialized = false;
};