#pragma once
#include "SDxBasic.h"

class SKeyInput
{
friend class SInputManager;
private:
	//===========================================================================
	// Direct Input Pointer
	//===========================================================================
	LPDIRECTINPUTDEVICE8	m_pDiKeyDevice;					// Ű���� ����̽�
	//===========================================================================
	// State Value
	//===========================================================================
	BYTE	m_KeyState[KEYSTATECOUNT];
	BYTE	m_KeyBeforeState[KEYSTATECOUNT];
	
public:
	//===========================================================================
	// Game FrameWork
	//===========================================================================
	bool			Init(LPDIRECTINPUT8	DirectInput, HWND hWnd);
	bool			Frame();
	bool			Render();
	bool			Release();
	//===========================================================================
	//	Other
	//===========================================================================
	DWORD			KeyCheck(DWORD dwKey);
	void			SetAcquire(bool bActive);

private:
	SKeyInput();
	~SKeyInput();
};

