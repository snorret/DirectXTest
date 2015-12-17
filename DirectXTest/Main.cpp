#include "windows.h"

#include "Window.h"
#include "MessagePump.h"

class Application
{
public:
	Application()
		: m_window(800, 600)
	{
	}

	void Run()
	{
		MessagePump messagePump;
		while (messagePump())
		{
		}
	}

private:
	Window m_window;
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Application app;
	app.Run();
	
	return 0;
}
