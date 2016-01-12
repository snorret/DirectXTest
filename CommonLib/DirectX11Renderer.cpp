#include "DirectX11Renderer.h"

#include "Window.h"

DirectX11Renderer::DirectX11Renderer(const Window & window)
{
	Init(window);
}

void DirectX11Renderer::Init(const Window & window)
{
	CreateDevice(window);
	CreateRenderTarget();
}

void DirectX11Renderer::CreateDevice(const Window & window)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.GetHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_deviceContext);

	if (result != S_OK)
	{
		MessageBox(nullptr, L"Failed to D3D11CreateDeviceAndSwapChain", L"Failure!", MB_OK);
		return;
	}
}

void DirectX11Renderer::CreateRenderTarget()
{
	ID3D11Texture2D * backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&backBuffer));
	m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->GetDesc(&m_backBufferDesc);
	backBuffer->Release();
}

DirectX11Renderer::~DirectX11Renderer()
{
	m_renderTargetView->Release();
	m_swapChain->Release();
	m_deviceContext->Release();
	m_device->Release();
}

void DirectX11Renderer::BeginFrame()
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, m_backBufferDesc.Width, m_backBufferDesc.Height);
	m_deviceContext->RSSetViewports(1, &viewport);

	float clearColor[] = { .25f, .5f, 1.f, 1.f };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}


void DirectX11Renderer::EndFrame()
{
	bool enableVsync = false;
	m_swapChain->Present(enableVsync ? 1 : 0, 0);
}

ID3D11Device * DirectX11Renderer::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext * DirectX11Renderer::GetDeviceContext()
{
	return m_deviceContext;
}