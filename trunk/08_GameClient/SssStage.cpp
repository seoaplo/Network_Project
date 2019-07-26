#include "SssStage.h"


bool SssStage::Init(HDC WindowDC, HDC OffScreen)
{
	MyWindowDC = WindowDC;
	MyOffScreenDC = OffScreen;

	MyScreen = CreateCompatibleDC(WindowDC);
	MyScreenBitMap = CreateCompatibleBitmap(WindowDC, 2048, 768);
	OldBitMap = (HBITMAP)SelectObject(MyScreen, MyScreenBitMap);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 2048;
	rect.bottom = 768;
	UINT Key = SingleImegeManeger.CreateImege(rect, L"../Data/StageGound.bmp", WindowDC);
	MyBackGroundImege = SingleImegeManeger.GetImege(Key);

	iSoundIndex = SingleSoundManeger.Load("../Data/sigma.mp3");
	
	MyPoint.x = 1024;
	MyPoint.y = 768 / 2;

	CameraPoint.x = 0;
	CameraPoint.y = 0;

	iChangeSceen = -1;

	fReadyTime = 0;
	fReadyMaxTime = 3.0f;

	bVictory = false;
	bLose = false;

	VictoryTime = 0.0f;
	VictoryMaxTime = 5.0f;
	LoseTime = 0.0f;
	LoseMaxTime = 5.0f;

#pragma region Ground
	SssObject* Object;
	Object = new SssGround;
	
	POINT Point;
	Point.x = 256 + 16;
	Point.y = 768 - 32;
	
	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssGround;

	Point.x = 256 + 512 + 16;
	Point.y = 768 -32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssGround;

	Point.x = 2048 - 256 - 16;
	Point.y = 768 - 32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssGround;

	Point.x = 2048 - 256 - 512 - 16;
	Point.y = 768 - 32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

#pragma endregion

#pragma region Cell
	Object = new SssGround;

	Point.x = 256;
	Point.y = -32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssGround;

	Point.x = 256 + 512;
	Point.y = -32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssGround;

	Point.x = 2048 - 256;
	Point.y = -32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssGround;

	Point.x = 2048 - 256 - 512;
	Point.y = -32;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);
#pragma endregion

#pragma region Wall
	Object = new SssWall;
	Point.x = 16;
	Point.y = 768 - (384 / 2);

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssWall;
	Point.x = 16;
	Point.y = 768 - 384 - (384 / 2);

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssWall;
	Point.x = 2048 - 16;
	Point.y = 768 - (384 / 2);

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssWall;
	Point.x = 2048 - 16;
	Point.y = 768 - 384 - (384 / 2);

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

#pragma endregion 

	SssMainBoss* MyBos = new SssMainBoss;
	Object = MyBos;
	Point.x = 900;
	Point.y = 768 - 32 -153 - 30;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	Object = new SssPlayer;
	Point.x = 100;
	Point.y = 768 - 92;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	MyBos->GetPlayer(*Object);

	SingleSoundManeger.Play(iSoundIndex, FMOD_LOOP_NORMAL);
	SingleSoundManeger.Volume(iSoundIndex, 0.5, false);

	Object = new SssPlayer;
	Point.x = 300;
	Point.y = 768 - 92;

	Object->Init(MyScreen, Point, WindowDC);
	MyObjectList.push_back(Object);

	MyBos->GetPlayer(*Object);

	SingleSoundManeger.Play(iSoundIndex, FMOD_LOOP_NORMAL);
	SingleSoundManeger.Volume(iSoundIndex, 0.5, false);
	return true;
}

bool SssStage::Frame()
{
	SingleInput.CheckKeyState(VK_SPACE);
	SingleInput.CheckKeyState(VK_SHIFT);
	SingleInput.CheckKeyState(VK_CONTROL);
	SingleInput.CheckKeyState(VK_ESCAPE);

	if (SingleInput.GetMyStateKey(VK_ESCAPE) == Key_Push)
	{
		bLose = true;
	}

	if (fReadyTime < fReadyMaxTime)
	{
		fReadyTime += GetSecPerFrame;
	}
	std::list<SssObject*>::iterator Itor;
	for (Itor = MyObjectList.begin(); Itor != MyObjectList.end(); Itor++)
	{
		if (dynamic_cast<SssPlayer*>(*Itor) != NULL)
		{
			if ((*Itor)->GetPos().x >= 516 && (*Itor)->GetPos().x <= 1536)
			{
				CameraPoint.x = (*Itor)->GetPos().x - 516;
			}
			else if ((*Itor)->GetPos().x < 516)
			{
				CameraPoint.x = 0;
			}
			else if ((*Itor)->GetPos().x < 1536)
			{
				CameraPoint.x = 1024;
			}
			SssPlayer* Player = dynamic_cast<SssPlayer*>(*Itor);
			if (fReadyTime < fReadyMaxTime)
			{
				Player->SetReady();
			}
			if (bVictory)
			{
				Player->SetVictory();
			}
			if (Player->GetDeath())
			{
				bLose = true;
			}
			Player->SetKeyState(VK_SPACE, SingleInput.GetMyStateKey(VK_SPACE));
			Player->SetKeyState(VK_SHIFT, SingleInput.GetMyStateKey(VK_SHIFT));
			Player->SetKeyState(VK_CONTROL, SingleInput.GetMyStateKey(VK_CONTROL));

			Player->SetKeyState('A', SingleInput.GetMyStateKey('A'));
			Player->SetKeyState('D', SingleInput.GetMyStateKey('D'));

		}
		if (dynamic_cast<SssMainBoss*>(*Itor) != NULL)
		{
			SssMainBoss* Boss = dynamic_cast<SssMainBoss*>(*Itor);
			if (fReadyTime < fReadyMaxTime)
			{
				Boss->SetReady();
			}
			if (bLose)
			{
				Boss->SetLose();
			}
			if (Boss->GetDeath())
			{
				bVictory = true;
			}
		}
		if (!(*Itor)->Frame())
		{
			return false;
		}
	}
	if (bVictory && VictoryTime < VictoryMaxTime)
	{
		VictoryTime += GetSecPerFrame;
		SingleSoundManeger.Volume(iSoundIndex, GetSecPerFrame / VictoryMaxTime, false);
	}
	else if (VictoryTime >= VictoryMaxTime)
	{
		iChangeSceen = SC_ResultWin;
	}
	if (bLose && LoseTime < LoseMaxTime)
	{
		LoseTime += GetSecPerFrame;
		SingleSoundManeger.Volume(iSoundIndex, GetSecPerFrame / LoseMaxTime, false);
	}
	else if(LoseTime >= LoseMaxTime)
	{
		iChangeSceen = SC_ResultLose;
	}
	
	return true;
}
bool SssStage::Render()
{
	COLORREF bkColor = RGB(255, 0, 0);
	HBRUSH hbrBack = CreateSolidBrush(bkColor);
	HBRUSH hbrOld = (HBRUSH)SelectObject(MyScreen, hbrBack);

	PatBlt(MyScreen, 0, 0, 2048, 768, PATCOPY);

	DeleteObject(SelectObject(MyScreen, hbrOld));

	MyBackGroundImege->Draw(MyScreen, MyPoint, 1, SRCCOPY);
	std::list<SssObject*>::iterator Itor;
	for (Itor = MyObjectList.begin(); Itor != MyObjectList.end(); Itor++)
	{
		(*Itor)->Render();
	}

	BitBlt(MyOffScreenDC, 0, 0, 1024, 768, MyScreen, CameraPoint.x, CameraPoint.y, SRCCOPY);
	return true;
}
bool SssStage::Release()
{
	std::list<SssObject*>::iterator Itor;
	for (Itor = MyObjectList.begin(); Itor != MyObjectList.end(); Itor++)
	{
		(*Itor)->Release();
		delete (*Itor);
		*Itor = nullptr;
	}
	MyObjectList.clear();
	SingleSoundManeger.Stop(iSoundIndex);
	DeleteObject(SelectObject(MyScreen, OldBitMap));
	DeleteDC(MyScreen);
	
	return true;
}


SssStage::SssStage()
{
}


SssStage::~SssStage()
{
}
