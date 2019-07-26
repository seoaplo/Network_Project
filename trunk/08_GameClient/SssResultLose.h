#pragma once
#include "SssSceeen.h"

class SssResultLose : public SssSceeen
{
	float MaxTime;
	float Time;
public:
	bool Init(HDC WindowDC, HDC OffScreen);
	bool Frame();
	bool Render();
	bool Release();
public:
	SssResultLose();
	~SssResultLose();
};

