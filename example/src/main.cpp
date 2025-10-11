#include <ssge.hpp>
#include <math.h>
#include <iostream>

class ExampleGameState : public GameStateBase
{
protected:
	static void OnBallCollisionEnter(const Sprite& other)
	{
		std::printf("Collision Enter\n");
	}

	static void OnBallCollisionExit(const Sprite& other)
	{
		std::printf("Collision Exit\n");
	}

public:
	~ExampleGameState() {}
    ExampleGameState()
     : ball("atlas.png", Rect({100, 76}, 16), SDL_SCALEMODE_NEAREST),
       ball2("atlas.png", Rect({100, 76}, 16), SDL_SCALEMODE_NEAREST)
    {
		_updateDelay = 1000.0f/60.0f; //i override the GameStateBase max fps.
		_physicsUpdateDelay = 1000.0f/60.0f;

		ball.gravityMultiplier = 0.0f;
		ball.SetOnCollisionEnterCallback(OnBallCollisionEnter);
		ball.SetOnCollisionExitCallback(OnBallCollisionExit);

		ball2.gravityMultiplier = 0.0f;
		ball2.SetOnCollisionEnterCallback(OnBallCollisionEnter);
		ball2.SetOnCollisionExitCallback(OnBallCollisionExit);

		ball2.SetPositionCentered(SSGE::GetRenderBounds() / 2.0f);
    }

protected:
	virtual EventHandlingResult HandleEvents(const SDL_Event& event) override
	{
        switch (event.type)
    	{
    	case SDL_EVENT_QUIT:
    		return EventHandlingResult::TerminateApplication;

    	case SDL_EVENT_KEY_DOWN:
    		if (event.key.repeat) break; //Voglio solo la pressione fisica.

    		switch (event.key.scancode)
    		{
    		case SDL_SCANCODE_ESCAPE:
    			return EventHandlingResult::TerminateApplication;

    		case SDL_SCANCODE_A:
    			movementInput.x -= 1;
    			break;
    		case SDL_SCANCODE_D:
    			movementInput.x += 1;
    			break;
    		case SDL_SCANCODE_S:
    			movementInput.y += 1;
    			break;
    		case SDL_SCANCODE_W:
    			movementInput.y -= 1;
    			break;

    		default:
    			break;
    		}
    		break;

    	case SDL_EVENT_KEY_UP:
    		switch (event.key.scancode)
    		{
    		case SDL_SCANCODE_A:
    			movementInput.x += 1;
    			break;
    		case SDL_SCANCODE_D:
    			movementInput.x -= 1;
    			break;
    		case SDL_SCANCODE_S:
    			movementInput.y -= 1;
    			break;
    		case SDL_SCANCODE_W:
    			movementInput.y += 1;
    			break;

    		default:
    			break;
    		}
    		break;
    	}

    	return EventHandlingResult::Continue;
	}

	virtual void PhysicsUpdate(double deltaTime) override
	{
		PhysicsEngine::AddForce(ball, (SSGE::GetMousePosition() - ball.GetPositionCentered()) * movementSpeed);
		PhysicsEngine::AddForce(ball2, (SSGE::GetMousePosition() - ball2.GetPositionCentered()) * movementSpeed);
	}

	virtual void Update(double deltaTime) override
	{
		GameStateBase::Update(deltaTime);
		ball.Rotate(deltaTime * sin(_timeSinceCreation) * 100.0f);
	}

	virtual void Render() override
	{
		SDL_RenderClear(const_cast<SDL_Renderer*>(SSGE::GetRenderer()));
		ball.DrawSelf();
		ball2.DrawSelf();
		SDL_RenderPresent(const_cast<SDL_Renderer*>(SSGE::GetRenderer()));
	}

	Sprite ball;
	Sprite ball2;
	Vector2 movementInput;
	float movementSpeed = 5.0f;
};

int main()
{
	//renderbounds must be exactly the ratio w/h, otherwise the images appear stretched. also it must be exact because SDL doesnt accept floats on the render scale...
	//for that choose your resolution and ratio consciously.
    SSGE::Init<ExampleGameState>("Finestra", {640 * 2, 360 * 2}, {16, 9});
    while (SSGE::Update());
    SSGE::Terminate();
}