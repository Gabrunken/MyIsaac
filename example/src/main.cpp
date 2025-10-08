#include <ssge.hpp>

class ExampleGameState : public GameStateBase
{
public:
    ExampleGameState()
     : ball("block.png", SDL_SCALEMODE_NEAREST)
    {}
	~ExampleGameState() {}

protected:
	float _updateDelay = 1000.0f/60.0f; //i override the GameStateBase max fps.

	virtual EventHandlingResult HandleEvents(const SDL_Event& event) override
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
    	}

    	return EventHandlingResult::Continue;
	}

	virtual void Update(float deltaTime) override
	{
		ball.Rotate(deltaTime * 10.0f);
	}

	virtual void Render() override
	{
		SDL_RenderClear(const_cast<SDL_Renderer*>(SSGE::GetRenderer()));
		ball.DrawSelf();
		SDL_RenderPresent(const_cast<SDL_Renderer*>(SSGE::GetRenderer()));
	}

	Sprite ball;
};

int main()
{
	//renderbounds must be exactly the ratio w/h, otherwise the images appear stretched. also it must be exact because SDL doesnt accept floats on the render scale...
	//for that choose your resolution and ratio consciously.
    SSGE::Init<ExampleGameState>("Finestra", {640, 360}, {16, 9});
    while (SSGE::Update());
    SSGE::Terminate();
}