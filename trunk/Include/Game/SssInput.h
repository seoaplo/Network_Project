#pragma once
#pragma once
#include "SssStd.h"

enum SssKeyState
{
	Key_Free = 0,
	Key_Push,
	Key_Hold,
	Key_Up
};

struct SssGetKeyState
{
	DWORD dwKeyW;
	DWORD dwKeyA;
	DWORD dwKeyS;
	DWORD dwKeyD;
	DWORD dwMouseL;
	DWORD dwMouseR;
	DWORD dwMouseM;
};

class SssInput
{
private:
	bool			MyDragCheck;
	POINT			MyMousePoint;
	POINT			MyMousePoint2;
	POINT			MyDragPoint;
	SssGetKeyState	MyKeyState;
	DWORD			MyKeyStateArray[MAX_PATH];
	HWND			MyhWindow;
public:
	virtual bool Init(HWND);
	virtual bool Frame();
	virtual bool Renderer();
	virtual bool Release();
public:
	DWORD			CheckKeyState(DWORD dwCheckKey);
	SssGetKeyState& GetKeyState()
	{
		return MyKeyState;
	}
	POINT& GetMousePoint()
	{
		return MyMousePoint;
	}
	POINT& GetMousePoint2()
	{
		return MyMousePoint2;
	}
	POINT& GetDragPoint()
	{
		return MyDragPoint;
	}
	DWORD GetMyStateKey(DWORD dwCheckKey)
	{
		return MyKeyStateArray[dwCheckKey];
	}
	static SssInput& GetInstance()
	{
		static SssInput SingleInput;
		return SingleInput;
	}
private:
	SssInput();
	~SssInput();
};

#define SingleInput SssInput::GetInstance()
#define GetKeyState SingleInput.GetKeyState()
#define GetMousePoint	SingleInput.GetMousePoint()
#define GetMousePoint2	SingleInput.GetMousePoint2()
#define GetDragPoint	SingleInput.GetDragPoint()
