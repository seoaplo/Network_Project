#pragma once
#include "SObjStd.h"

class SModel
{
public:
	ID3D11Device*						m_pd3dDevice;
	ID3D11DeviceContext*				m_pContext;
	DX::SDxObject						m_dxobj;
	D3D11_SHADER_RESOURCE_VIEW_DESC		m_TextureDesc;

	VS_CONSTANT_BUFFER			m_cbData;
	D3DXVECTOR3					m_vCenter;
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	vector<DWORD>				m_IndexList;
	vector<PNCT_VERTEX>			m_VertexList;

public:
	//----------------------------------------------------------------------------------------------------------
	// Getter
	//----------------------------------------------------------------------------------------------------------
	ID3D11Buffer*				GetVB();
	ID3D11Buffer*				GetIB();
	virtual	int					GetMeshCounter() { return 0; }
	//----------------------------------------------------------------------------------------------------------
	// Setter
	//----------------------------------------------------------------------------------------------------------
	virtual void				SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	virtual void				SetAmbientColor(float fR, float fG, float fB, float fA);
	virtual HRESULT				SetInputLayout();
	//----------------------------------------------------------------------------------------------------------
	// Create
	//----------------------------------------------------------------------------------------------------------
	virtual bool				Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString = 0);
	virtual bool				CreateVertexData();
	virtual bool				CreateIndexData();
	virtual HRESULT				CreateVertexBuffer();
	virtual HRESULT				CreateIndexBuffer();
	virtual HRESULT				CreateConstantBuffer();
	virtual HRESULT				CreateResource();
	//----------------------------------------------------------------------------------------------------------
	// Load
	//----------------------------------------------------------------------------------------------------------

	virtual bool				Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread = false);
	virtual HRESULT				LoadShaderFile(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile);
	virtual HRESULT				LoadTextures(ID3D11Device* pDevice, const TCHAR* pLoadTextureString);

	//----------------------------------------------------------------------------------------------------------
	// Frame Work
	//----------------------------------------------------------------------------------------------------------
	virtual bool				Init();
	virtual bool				Frame();
	virtual bool				PreRender(ID3D11DeviceContext* pContext);
	virtual bool				Render(ID3D11DeviceContext*		pContext);
	virtual bool				PostRender(ID3D11DeviceContext* pContext);
	virtual bool				Release();

	//----------------------------------------------------------------------------------------------------------
	// etc
	//----------------------------------------------------------------------------------------------------------
	virtual bool				Convert(ID3D11Device* pDevice);
	virtual HRESULT				DeleteResource();
	virtual bool				UpdateBuffer();
	// ���� ���ؽ�Ʈ�� ���ÿ� ��� ���ؽ�Ʈ�� �����ϱ� ���ؼ� �������� ���� �Լ�ȭ �Ͽ���.
	virtual void				UpdateConstantBuffer(ID3D11DeviceContext* pContext, SModel* pParent = nullptr);
	virtual bool				Draw(ID3D11DeviceContext* pContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor);

	SModel();
	virtual ~SModel();
};
