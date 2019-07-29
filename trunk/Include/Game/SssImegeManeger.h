#pragma once
#include "SssImege.h"

enum ObjectNumber
{
	Hero = 0,
	Enemy,
	BG	
};

class SssImegeManeger
{
private:
	std::map<UINT, SssImege*> ObjectList;
	UINT iSize;
public:
	UINT CreateImege(RECT ObjectSize, const TCHAR* RouteTString, HDC MyWindowDC);
	SssImege* GetImege(UINT& iKey);
	bool Release();
	static SssImegeManeger& GetInstance()
	{
		static SssImegeManeger SingleObjectManeger;
		return SingleObjectManeger;
	}
private:
	SssImegeManeger();
	~SssImegeManeger();
};

#define SingleImegeManeger SssImegeManeger::GetInstance()