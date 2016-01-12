#pragma once

#include "D3D11.h"

class Window;

class DirectX11Renderer
{
public:
	DirectX11Renderer(const Window & window);
	~DirectX11Renderer();

	void BeginFrame();
	void EndFrame();

	ID3D11Device * GetDevice();
	ID3D11DeviceContext * GetDeviceContext();

private:
	void Init(const Window & window);
	void CreateDevice(const Window & window);
	void CreateRenderTarget();

	IDXGISwapChain * m_swapChain = nullptr;
	ID3D11Device * m_device = nullptr;
	ID3D11DeviceContext * m_deviceContext = nullptr;
	ID3D11RenderTargetView * m_renderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_backBufferDesc;
};