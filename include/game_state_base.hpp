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

	GameStateBase() = default;
	virtual ~GameStateBase() = default;

protected:
	/*
	* Any save upon close logic should be written inside this function, since when you return TerminateApplication it does not pass its last execution to Update.
	*/
	virtual EventHandlingResult HandleEvents(const SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	friend class GameStateManager;

	float _updateDelay = 1000.0f/60.0f; //60 is a default value, every child can change its.
};