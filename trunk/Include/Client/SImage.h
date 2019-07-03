#pragma once
#include "SShape.h"

class SImage
{
public:
	SShape* m_pPlane;
	ID3D11DeviceContext* m_pContext;
	D3D11_TEXTURE2D_DESC m_TextureDesc;

	T_STR			m_TexturePath;
	//==============================================================================================
	// Matrix
	//==============================================================================================
	D3DXMATRIX m_matTranslation;
	D3DXMATRIX m_matSpin;
	D3DXMATRIX m_matScale;

public:
	bool	CreateImage(ID3D11Device* pDevice, const T_STR pLoadShaderFile, const T_STR pLoadTextureString);

	//==============================================================================================
	// Frame Work
	//==============================================================================================
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	//==============================================================================================
	// Setter
	//==============================================================================================
	void SetSpin(float fRadian);
	void SetScale(D3DXVECTOR3 vScale);
	void SetTranslation(D3DXVECTOR3 vMove);
	void SetAmbientColor(D3DXVECTOR4 vColor);
	bool SetTextureCoord(PLANE_TEXTURECOORD CoordArray);
	bool SetVertexList(PLANE_PNCTLIST PNCTList);

	void SetView(D3DXMATRIX matView);
	void SetProjection(D3DXMATRIX matProj);
	
public:
	SImage();
	~SImage();
};

