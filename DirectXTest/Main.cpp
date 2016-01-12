#include "windows.h"

#include "Window.h"
#include "MessagePump.h"
#include "DirectX11Renderer.h"
#include "Triangle.h"


class Application
{
public:
	Application()
		: m_window(800, 600)
		, m_renderer(m_window)
		, m_triangle(m_renderer)
	{
	}

	void Run()
	{
		MessagePump messagePump;
		while (messagePump())
		{
			m_renderer.BeginFrame();

			m_triangle.Draw(m_renderer);

			m_renderer.EndFrame();
		}
	}

private:
	Window m_window;
	DirectX11Renderer m_renderer;
	Triangle m_triangle;
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Application app;
	app.Run();

	return 0;
}
