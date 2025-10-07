#include <ssge.hpp>

class ExampleGameState : public GameStateBase
{
public:
    ExampleGameState() {}
	~ExampleGameState() {}

protected:
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

	}

	virtual void Render() override
	{

	}
};

int main()
{
    SSGE::Init<ExampleGameState>("Finestra", {720, 480}, {16, 9});
    while (SSGE::Update());
    SSGE::Terminate();
}