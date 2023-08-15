#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const vector<VertexType>& vertices, const vector<DWORD>& indices)
	: device(device), deviceContext(deviceContext), vertexBuffer(nullptr), indexBuffer(nullptr)
{
	if (!CreateVertexBuffer(vertices))
	{
		return;
	}

	if (!CreateIndexBuffer(indices))
	{
		return;
	}
}

void Mesh::Draw()
{
	uint offset;
	uint stride;

	offset = 0;
	stride = sizeof(VertexType);

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

ID3D11Buffer* Mesh::CreateVertexBuffer(const vector<VertexType>& vertices)
{
	// Safety
	if (vertexBuffer != nullptr) { vertexBuffer->Release(); }

	this->stride = std::make_shared<UINT>(sizeof(vertices.data()));

	// Set up the description of the static vertex buffer.
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	{
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(VertexType) * vertices.size());
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
	}

	// Set up subresource structure a pointer to the vertex data.
	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
	{
		vertexData.pSysMem = vertices.data();
	}

	// Create the vertex buffer.
	HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(result))
	{
		return nullptr;
	}

	return vertexBuffer;
}

ID3D11Buffer* Mesh::CreateIndexBuffer(const vector<DWORD>& indices)
{
	// Safety
	if (indexBuffer != nullptr) { indexBuffer->Release(); }

	this->bufferSize = indices.size();

	// Set up the description of the static index buffer.
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	{
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(DWORD) * indices.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
	}

	// Set up subresource structure a pointer to the index data.
	D3D11_SUBRESOURCE_DATA indexData;
	ZeroMemory(&indexData, sizeof(indexData));
	{
		indexData.pSysMem = indices.data();
	}

	// Create the index buffer.
	HRESULT result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result))
	{
		return nullptr;
	}

	return indexBuffer;
}
