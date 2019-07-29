#include "SssEffect.h"



bool SssEffect::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const TCHAR* RouteString, const TCHAR* RectString,
	COLORREF COLOR, const TCHAR* RectRouteString, const char* SoundString, float LifeSecond)
{
	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 1024, 768);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	MyPos.x = TargetPos.x;
	MyPos.y = TargetPos.y;

	int SpriteNumber;
	SpriteNumber = SingleSpriteManeger.CreateSprite
	(RectRouteString, RouteString, RectString, COLOR, WindowDC, LifeSecond);
	SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);

	if (SoundString != NULL)
		iSoundIndex = SingleSoundManeger.Load(SoundString);
	else
		iSoundIndex = -1;
	MaxLifeSecond = LifeSecond;

	return true;
}
bool SssEffect::Frame()
{
	std::vector<DrawData*> DeleteData;
	DeleteData.reserve(DrawList.size());
	SpriteImege->Frame();
	for (std::list<DrawData*>::iterator Itor = DrawList.begin(); Itor != DrawList.end(); Itor++)
	{
		(*Itor)->LifeTime += GetSecPerFrame;
		if ((*Itor)->LifeTime >= MaxLifeSecond)
		{
			delete (*Itor);
			DeleteData.push_back(*Itor);
		}
		else
		{
			(*Itor)->MySprite.Frame();
		}
	}
	for (UINT iCount = 0; iCount < DeleteData.size(); iCount++)
	{
		DrawList.remove(DeleteData[iCount]);
	}
	DeleteData.clear();
	return true;
}
bool SssEffect::Render()
{
	std::list<DrawData*>::iterator Itor;
	for (Itor = DrawList.begin(); Itor != DrawList.end(); Itor++)
	{
		(*Itor)->MySprite.Draw(MyOffScreen, (*Itor)->MyPos, (*Itor)->Scale, (*Itor)->DrawOption);
		if (!(*Itor)->bSoundStart && iSoundIndex != -1)
		{
			SingleSoundManeger.PlayEffect(iSoundIndex);
			SingleSoundManeger.Volume(iSoundIndex, 0.2, false);
			(*Itor)->bSoundStart = true;
		}
	}
	return true;
}
bool SssEffect::Release()
{
	std::list<DrawData*>::iterator Itor;
	for (Itor = DrawList.begin(); Itor != DrawList.end(); Itor++)
	{
		delete (*Itor);
	}
	DrawList.clear();
	return true;
}
void SssEffect::SetDrawData(POINT TargetPos, float TargetScale, int TargetDrawOption)
 {
	DrawData* TargetData = new DrawData;
	TargetData->LifeTime = 0.0f;
	TargetData->MyPos = TargetPos;
	TargetData->bSoundStart = false;
	TargetData->Scale = TargetScale;
	TargetData->MySprite = *SpriteImege;
	TargetData->DrawOption = TargetDrawOption;
	TargetData->MySprite.Init();
	DrawList.push_back(TargetData);
}

SssEffect::SssEffect()
{
}


SssEffect::~SssEffect()
{
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
}
