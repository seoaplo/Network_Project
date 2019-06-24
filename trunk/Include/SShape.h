#pragma once
#include "SModel.h"

class SShape : public SModel
{
public:
//--------------------------------------------------------------------------------------
// Collision Data
//--------------------------------------------------------------------------------------
public:
	virtual bool SetVertexData(ID3D11DeviceContext* pContext, vector<PNCT_VERTEX>& TargetVertexList) { return true; }
	virtual bool SetScreenVertex(float x, float y, float w,	float h, D3DXVECTOR2 vScreen) { return true;}
	SShape();
	virtual ~SShape();
};

class SLineShape : public SShape
{
public:
	vector<PC_VERTEX>	m_LineVertexList;
public:
	HRESULT				SetInputLayout();
	bool				CreateVertexData();
	bool				CreateIndexData();
	HRESULT				CreateVertexBuffer();
	HRESULT				CreateResource();
	bool				Draw(ID3D11DeviceContext* pContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 dwColor);
public:
	SLineShape();
	virtual ~SLineShape();
};

class SDirectionLineShape : public SShape
{
public:
	vector<PC_VERTEX>	m_LineVertexList;
public:
	HRESULT				SetInputLayout();
	bool				CreateVertexData();
	bool				CreateIndexData();
	HRESULT				CreateVertexBuffer();
	HRESULT				CreateResource();
public:
	SDirectionLineShape();
	virtual ~SDirectionLineShape();
};

class SPlaneShape : public SShape
{
public:
	bool			CreateVertexData();
	bool			CreateIndexData();
	HRESULT			CreateResource();
	bool SetScreenVertex(float x,
		float y,
		float w,
		float h,
		D3DXVECTOR2 vScreen);
public:
	bool SetVertexData(ID3D11DeviceContext* pContext, vector<PNCT_VERTEX>& TargetVertexList);

public:
	SPlaneShape(void);
	virtual ~SPlaneShape(void);
};
