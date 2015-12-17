#include "Window.h"

#include "Windows.h"

LRESULT CALLBACK winProc(HWND hwnd, unsigned int msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY || msg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

struct Window::pImpl
{
	HWND hwnd;
};

Window::Window(int width, int height)
	: m_pImpl{ std::make_unique<pImpl>() }
{
	Create(width, height);
}

void Window::Create(int width, int height)
{
	WNDCLASS windowClass = { 0 };
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = winProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = L"DirectXTestWindowClassName";
	RegisterClass(&windowClass);

	const LPCWSTR windowName = L"Tezt";
	const unsigned int windowStyle = WS_POPUP | WS_CAPTION | WS_VISIBLE;
	const int posX = 100;
	const int posY = 100;
	m_pImpl->hwnd = CreateWindow(L"DirectXTestWindowClassName", windowName, windowStyle, posX, posY, width, height, nullptr, nullptr, nullptr, nullptr);
}

Window::~Window()
{
	DestroyWindow(m_pImpl->hwnd);
}
