#pragma once
#include "SClient.h"
#include "SssSceeen.h"
#include "SssPlayer.h"
#include "SssWall.h"
#include "SssMainBoss.h"

class SssStage : public SssSceeen
{
public:
	HDC MyScreen;
	HBITMAP MyScreenBitMap;
	HBITMAP OldBitMap;
	POINT CameraPoint;
	std::list<SssObject*> MyObjectList;

	std::vector<SssPlayer> m_PlayerArray;
	std::vector<SssWall> m_WallArray;
	std::vector<SssGround> m_GroundArray;
	SssMainBoss* MyBos;

	float fReadyTime;
	float fReadyMaxTime;
	int iSoundIndex;
	bool bVictory;
	bool bLose;
	float VictoryTime;
	float VictoryMaxTime;
	float LoseTime;
	float LoseMaxTime;

	SClient m_Client;

	int		m_iIndex;
	bool	m_bLogin;
	float	m_fLoginWait;
	std::string PlayerName;

	HWND	m_hLogin;
	HWND	m_hEdit;
	HWND	m_hButton;
public:
	virtual bool Init(HDC WindowDC, HDC OffScreen);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	bool PacketProcess();
	LRESULT MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
public:
	bool InitPlayerArray();
	bool InitWallArray();
	bool InitGroundArray();
	bool InitBoss();
public:
	SssStage();
	~SssStage();
};

