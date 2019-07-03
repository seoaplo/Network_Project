#pragma once
#include "SImageManager.h"
#include "STimer.h"

class SSpriteManager;
class SSprite
{
friend class SSpriteManager;
//========================================================================
// 좌표값 리스트
//========================================================================
	std::vector<PLANE_PNCTLIST> m_SpriteVertex;
	std::vector<D3DXVECTOR2> m_VertexCenterList;
	
//========================================================================
// 스프라이트 상태 값
//========================================================================
	int m_iMaxIndex;
	int m_iPlayIndex;
	int m_iLoopIndex;

	float m_fPlayTime;
	float m_fDrawTime;
	float m_fCheckTime;

	bool m_bLoop;

	float m_fRadian;
	D3DXVECTOR3 m_vScale;
	D3DXVECTOR3 m_vMove;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXVECTOR4 m_vColor;
//========================================================================
// etc
//========================================================================
	SImage*	m_pImage;
	STimer	m_Timer;
	T_STR	m_SpriteName;
public:

	bool CreateSprite(std::vector<PLANE_PNCTLIST>& TargetCoord, TCHAR* SpriteName, SImage* Image, int LoopFrame);

//========================================================================
// Getter
//========================================================================
	int GetPlayIndex() { return m_iPlayIndex; };
	int GetLoopIndex() { return m_iLoopIndex; };

//========================================================================
// Setter
//========================================================================

	void SetSpin(float fRadian)						{ m_fRadian = fRadian; }
	void SetScale(D3DXVECTOR3 vScale)				{ m_vScale = vScale; }
	void SetTranslation(D3DXVECTOR3 vMove)			{ m_vMove = vMove; }
	void SetView(D3DXMATRIX matView)				{ m_matView = matView; }
	void SetProjection(D3DXMATRIX matProj)			{ m_matProj = matProj; }
	void SetAmbientColor(D3DXVECTOR4 vColor)		{ m_vColor = vColor; }
	void SetLoop(bool bLoop)						{ m_bLoop = bLoop;	}
	void SetPlayTime(float fPlayTime)				{ m_fPlayTime = fPlayTime; m_fDrawTime = m_fPlayTime / m_iMaxIndex;}
	void SetPlayIndex(int iPlayIndex)				{ m_iPlayIndex  = iPlayIndex; };
	void SetLoopIndex(int iLoopIndex)				{ m_iLoopIndex  = iLoopIndex; };
	void Reset();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	SSprite();
	~SSprite();
};

