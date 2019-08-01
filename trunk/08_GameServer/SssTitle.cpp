#include "SssTitle.h"



bool SssTitle::Init(HDC WindowDC, HDC OffScreen)
{
	MyWindowDC = WindowDC;
	MyOffScreenDC = OffScreen;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 1024;
	rect.bottom = 768;
	UINT Key = SingleImegeManeger.CreateImege(rect, L"../../../data/Title1.bmp", WindowDC);
	MyBackGroundImege = SingleImegeManeger.GetImege(Key);
	MyPoint.x = 1024 / 2;
	MyPoint.y = 768 / 2;
	iChangeSceen = -1;

	

	COLORREF Color = RGB(29, 112, 189);
	SssTitleObject* TitleName = new SssTitleObject;
	POINT TitleNamePos;
	TitleNamePos.x = 450;
	TitleNamePos.y = 200;
	RECT TitleNameRect;
	TitleNameRect.left = 0;
	TitleNameRect.top = 0;
	TitleNameRect.right = 0;
	TitleNameRect.bottom = 0;
	TitleName->Init(MyOffScreenDC, TitleNamePos, WindowDC, NULL, TitleNameRect, L"../../../data/BackGround3.bmp", L"RectTitle1",
		L"../../../data/TitleRect1.txt", Color, false, 2);
	TitleObjectList.push_back(TitleName);

	TitleName = new SssTitleObject;
	POINT TitleNamePos1;
	TitleNamePos1.x = 670;
	TitleNamePos1.y = 200;
	RECT TitleNameRect1;
	TitleNameRect1.left = 0;
	TitleNameRect1.top = 0;
	TitleNameRect1.right = 0;
	TitleNameRect1.bottom = 0;
	TitleName->Init(MyOffScreenDC, TitleNamePos1, WindowDC, NULL, TitleNameRect1, L"../../../data/BackGround3.bmp", L"RectTitle2",
		L"../../../data/TitleRect1.txt", Color, false, 2);
	TitleObjectList.push_back(TitleName);

	TitleName = new SssStartObject;
	POINT TitleNamePos2;
	TitleNamePos2.x = 517;
	TitleNamePos2.y = 410;
	RECT TitleNameRect2;
	TitleNameRect2.left = 517;
	TitleNameRect2.top = 410;
	TitleNameRect2.right = 87 * 4;
	TitleNameRect2.bottom = 7 * 4;
	TitleName->Init(MyOffScreenDC, TitleNamePos2, WindowDC, "../../../data/Select.wav", TitleNameRect2, L"../../../data/BackGround3.bmp", L"RectStartGame",
		L"../../../data/TitleRect1.txt", Color, true, 4);
	TitleObjectList.push_back(TitleName);

	TitleName = new SssExitObject;
	POINT TitleNamePos3;
	TitleNamePos3.x = 517;
	TitleNamePos3.y = 500;
	RECT TitleNameRect3;
	TitleNameRect3.left = 517;
	TitleNameRect3.top = 450;
	TitleNameRect3.right = 32 * 4;
	TitleNameRect3.bottom = 7 * 4;
	TitleName->Init(MyOffScreenDC, TitleNamePos3, WindowDC, "../../../data/Select.wav", TitleNameRect3, L"../../../data/BackGround3.bmp", L"RectExit",
		L"../../../data/TitleRect1.txt", Color, true, 4);
	TitleObjectList.push_back(TitleName);

	iSoundIndex = SingleSoundManeger.Load("../../../data/Title.wav");
	SingleSoundManeger.Play(iSoundIndex, FMOD_LOOP_NORMAL);

	SingleSoundManeger.Volume(iSoundIndex, 0.5f, false);

	return true;
}

bool SssTitle::Frame()
{
	std::list<SssTitleObject*>::iterator Itor;
	for (Itor = TitleObjectList.begin(); Itor != TitleObjectList.end(); Itor++)
	{
		if (!(*Itor)->Frame())
		{
			return false;
		}
		if ((*Itor)->GetChangeSceen())
		{
			iChangeSceen = SC_Stage;
			SingleSoundManeger.Volume(iSoundIndex, GetSecPerFrame, false);
		}
	}
	return true;
}
bool SssTitle::Render()
{
	MyBackGroundImege->Draw(MyOffScreenDC, MyPoint, 1, SRCCOPY);
	std::list<SssTitleObject*>::iterator Itor;
	for (Itor = TitleObjectList.begin(); Itor != TitleObjectList.end(); Itor++)
	{
		(*Itor)->Render();
	}
	return true;
}
bool SssTitle::Release()
{
	std::list<SssTitleObject*>::iterator Itor;
	for (Itor = TitleObjectList.begin(); Itor != TitleObjectList.end(); Itor++)
	{
		(*Itor)->Release();
		delete (*Itor);
	}
	SingleSoundManeger.Stop(iSoundIndex);
	
	iSoundIndex = -1;
	TitleObjectList.clear();
	return true;
}
