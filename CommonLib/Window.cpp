#include "Window.h"

#include "Windows.h"
#include "tchar.h"

LRESULT CALLBACK WinProc(HWND hwnd, unsigned int msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
		break;
	}
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
	const wchar_t * WindowClassName = L"DirectXTestWindowClassName";

	WNDCLASS windowClass = { 0 };
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = WinProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = WindowClassName;
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	if (!RegisterClass(&windowClass))
	{
		MessageBox(nullptr, L"Failed to RegisterClass", L"Failure!", MB_OK);
		return;
	}

	const LPCWSTR windowName = L"Tezt";
	const unsigned int windowStyle = WS_POPUP | WS_CAPTION | WS_VISIBLE | WS_SYSMENU;
	const int posX = 100;
	const int posY = 100;
	m_pImpl->hwnd = CreateWindow(WindowClassName, windowName, windowStyle, posX, posY, width, height, nullptr, nullptr, nullptr, nullptr);
	
	if (!m_pImpl->hwnd)
	{
		MessageBox(nullptr, L"Failed to CreateWindow", L"Failure!", MB_OK);
		return;
	}
}

HWND Window::GetHandle() const
{
	return m_pImpl->hwnd;
}

Window::~Window()
{
	DestroyWindow(m_pImpl->hwnd);
}
