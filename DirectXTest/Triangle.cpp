#include "Triangle.h"

#include <fstream>
#include <vector>

struct Vertex
{
	float x, y;
	float r, g, b;
};

Triangle::Triangle(DirectX11Renderer & renderer)
{
	CreateMesh(renderer);
	CreateShaders(renderer);
}

void Triangle::CreateMesh(DirectX11Renderer & renderer)
{
	Vertex vertices[] =
	{
		{ -1.f, -1.f, 1.f, 0.f, 0.f },
		{ 0.f, 1.f, 0.f, 1.f, 0.f },
		{ 1.f, -1.f, 0.f, 0.f, 1.f },
	};

	auto vertextBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	auto result = renderer.GetDevice()->CreateBuffer(&vertextBufferDesc, &vertexData, &m_vertexBuffer);
	if (result != S_OK)
	{
		MessageBox(nullptr, L"Failed to CreateBuffer", L"Failure!", MB_OK);
		return;
	}
}

void Triangle::CreateShaders(DirectX11Renderer & renderer)
{
	std::ifstream vsFile("TriangleVS.cso", std::ios::binary);
	std::ifstream psFile("TrianglePS.cso", std::ios::binary);
	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	renderer.GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	renderer.GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	
	renderer.GetDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}

Triangle::~Triangle()
{
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
}

void Triangle::Draw(DirectX11Renderer & renderer)
{
	ID3D11DeviceContext * deviceContext = renderer.GetDeviceContext();

	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->Draw(3, 0);
}