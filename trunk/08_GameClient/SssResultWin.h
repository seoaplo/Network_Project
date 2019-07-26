#pragma once
#include "SssSceeen.h"

class SssResultWin : public SssSceeen
{
	float MaxTime;
	float Time;
public:
	bool Init(HDC WindowDC, HDC OffScreen);
	bool Frame();
	bool Render();
	bool Release();
public:
	SssResultWin();
	~SssResultWin();
};

