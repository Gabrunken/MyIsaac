#pragma once
#include <SDL3/SDL.h>

enum class EventHandlingResult
{
	TerminateApplication,
	Continue
};

typedef void (*UpdateCallback) (double deltaTime);
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
	virtual void Update(double deltaTime) {_timeSinceCreation += deltaTime;}

	//This method must contain all the physics logic and calculations,
	//since the equations work out only if the deltaTime is fixed, for that it will be called at a fixed rate.
	//Every physics object should only call physics functions to apply forces to each other.
	//The deltaTime might not be necessary since i already pass it and do the calculations inside PhysicsEngine.
	virtual void PhysicsUpdate(double deltaTime) = 0;

	virtual void Render() = 0;

	friend class GameStateManager;

	//All this parameter are of course overridable
	double _updateDelay = 1000.0f/60.0f;

	//Since this runs on the main loop thread,
	//capping this to a greater update rate per second than the main loop's, will only result
	//at it being capped at the same rate as the main loop's.
	double _physicsUpdateDelay = 1000.0f/30.0f;

	double _timeSinceCreation = 0.0f;
};