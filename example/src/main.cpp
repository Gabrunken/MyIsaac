#include <ssge.hpp>
#include <math.h>

class ExampleGameState : public GameStateBase
{
public:
	~ExampleGameState() {}
    ExampleGameState()
     : ball("atlas.png", Rect({100, 76}, 16), SDL_SCALEMODE_NEAREST)
    {}

protected:
	float _updateDelay = 1000.0f/60.0f; //i override the GameStateBase max fps.

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

	virtual void Update(float deltaTime) override
	{
		GameStateBase::Update(deltaTime);
		ball.Rotate(deltaTime * sin(_timeSinceCreation) * 100.0f);
		ball.Move(movementInput.GetNormalized() * deltaTime * movementSpeed);
	}

	virtual void Render() override
	{
		SDL_RenderClear(const_cast<SDL_Renderer*>(SSGE::GetRenderer()));
		ball.DrawSelf();
		SDL_RenderPresent(const_cast<SDL_Renderer*>(SSGE::GetRenderer()));
	}

	Sprite ball;
	Vector2 movementInput;
	float movementSpeed = 3.0f;
};

int main()
{
	//renderbounds must be exactly the ratio w/h, otherwise the images appear stretched. also it must be exact because SDL doesnt accept floats on the render scale...
	//for that choose your resolution and ratio consciously.
    SSGE::Init<ExampleGameState>("Finestra", {640 * 2, 360 * 2}, {16, 9});
    while (SSGE::Update());
    SSGE::Terminate();
}