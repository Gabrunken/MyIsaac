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
	GameStateBase() = default;
	GameStateBase(const GameStateBase& other) = delete;
	void operator=(const GameStateBase& other) = delete;

	virtual ~GameStateBase() = default;

protected:
	/*
	* Any save upon close logic should be written inside this function, since when you return TerminateApplication it does not pass its last execution to Update.
	*/
	virtual EventHandlingResult HandleEvents(const SDL_Event& event) = 0;
	//Children must call this function inside their override.
	virtual void Update(float deltaTime) {_timeSinceCreation += deltaTime;}
	virtual void Render() = 0;

	friend class GameStateManager;

	float _updateDelay = 1000.0f/60.0f; //60 is a default value, every child can change its.
	float _timeSinceCreation = 0.0f;
};