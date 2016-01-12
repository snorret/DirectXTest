#pragma once

#include <windows.h>
#include <memory>

class Window
{
public:
	Window(int width, int height);
	~Window();

	HWND GetHandle() const;

private:
	void Create(int width, int height);

	struct pImpl;
	std::unique_ptr<pImpl> m_pImpl;
};

