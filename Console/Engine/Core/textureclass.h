////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class TextureClass
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*);
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& filePath);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

	int GetWidth();
    int GetHeight();

private:
	bool LoadWICTexture(const std::string& filePath);
	bool LoadTarga32Bit(const char*);

private:
	ID3D11Device*		 device;
	ID3D11DeviceContext* deviceContext;

	unsigned char* m_targaData;
	ID3D11Texture2D* m_texture;
	ID3D11Resource* resource;
	ID3D11ShaderResourceView* m_textureView;
	int m_width, m_height;
};

#endif