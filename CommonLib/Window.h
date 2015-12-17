#pragma once

#include <memory>

class Window
{
public:
	Window(int width, int height);
	~Window();

private:
	void Create(int width, int height);

	struct pImpl;
	std::unique_ptr<pImpl> m_pImpl;
};

