#include <windows.h>

#include <Window.h>

class Application
{
public:
	Application()
		: m_window(800, 600)
	{
	}

	void Run()
	{
		while (true)
		{
			ProcessWindowsMessages();
		}
	}

	bool ProcessWindowsMessages()
	{
		MSG msg = { 0 };
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				return false;
			}
		}

		return true;
	}

private:
	Window m_window;
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Application app;
	

	return 0;
}
