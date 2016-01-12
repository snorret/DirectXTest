#pragma once

#include "DirectX11Renderer.h"

class Triangle
{
public:
	Triangle(DirectX11Renderer & renderer);
	~Triangle();

	void Draw(DirectX11Renderer & renderer);

private:
	void CreateMesh(DirectX11Renderer & renderer);
	void CreateShaders(DirectX11Renderer & renderer);

	ID3D11Buffer * m_vertexBuffer = nullptr;
	ID3D11VertexShader * m_vertexShader = nullptr;
	ID3D11PixelShader * m_pixelShader = nullptr;
	ID3D11InputLayout * m_inputLayout = nullptr;
};

