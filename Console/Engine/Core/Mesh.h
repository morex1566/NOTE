#pragma once
class Mesh
{
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const vector<VertexType>& vertices, const vector<DWORD>& indices);

	void Draw();

	const UINT Stride() const
	{
		return *this->stride.get();
	}

	const UINT* StridePtr() const
	{
		return this->stride.get();
	}

private:
	ID3D11Buffer* CreateVertexBuffer(const vector<VertexType>& vertices);
	ID3D11Buffer* CreateIndexBuffer(const vector<DWORD>& indices);

private:
	ID3D11Device*				device;
	ID3D11DeviceContext*		deviceContext;
	ID3D11Buffer*				vertexBuffer;
	ID3D11Buffer*				indexBuffer;
	std::shared_ptr<UINT>		stride;
	UINT						bufferSize;
};