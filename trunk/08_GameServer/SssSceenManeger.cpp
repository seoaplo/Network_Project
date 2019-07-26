#include "SssSceenManeger.h"



bool SssSceenManeger::Init(HDC TargetOffScreenDC, HDC TargetWindowDC)
{
	MyOffScreen = TargetOffScreenDC;
	MyWindowScreen = TargetWindowDC;
	MyBlendScreen = CreateCompatibleDC(TargetWindowDC);
	MyBlendBitMap = CreateCompatibleBitmap(TargetWindowDC, 1024, 768);
	MyOldBitMap = (HBITMAP)SelectObject(MyBlendScreen, MyBlendBitMap);

	COLORREF BkColor = RGB(0, 0, 0);
	HBRUSH Brush = CreateSolidBrush(BkColor);
	HBRUSH OldBrush = (HBRUSH)SelectObject(MyBlendScreen, Brush);
	PatBlt(MyBlendScreen, 0, 0, 1024, 768, PATCOPY);
	DeleteObject(SelectObject(MyBlendScreen, OldBrush));

	ChangeSceenTime = 0.0f;
	ChangeSceenMaxTime = 2.0f;
	fAlpha = 0.0f;

	MySceen = new SssTitle;
	MySceenList.insert(std::make_pair(SC_TITLE, MySceen));

	MySceen = new SssStage;
	MySceenList.insert(std::make_pair(SC_Stage, MySceen));

	MySceen = new SssResultLose;
	MySceenList.insert(std::make_pair(SC_ResultLose, MySceen));

	MySceen = new SssResultWin;
	MySceenList.insert(std::make_pair(SC_ResultWin, MySceen));

	bChange = false; 

	std::map<DWORD, SssSceeen*>::iterator Itor;
	Itor = MySceenList.find(SC_TITLE);
	MySceen = Itor->second;
	MySceen->Init(MyWindowScreen, MyOffScreen);
	return true;
}
bool SssSceenManeger::Frame()
{
	if (MySceen->GetSceenChanege() >= 0)
	{
		ChangeSceen(MySceen->GetSceenChanege());
	}
	if (bChange)
	{
		ChangeSceenTime += GetSecPerFrame;

		if (ChangeSceenTime < (ChangeSceenMaxTime / 2))
		{
			if (fAlpha >= 1)
			{
				fAlpha = 1.0f;
			}
			else
			{
				fAlpha += GetSecPerFrame;
			}
			MyOldSceen->Frame();
		}
		else if ((ChangeSceenMaxTime / 2) < ChangeSceenTime && ChangeSceenTime < ChangeSceenMaxTime)
		{
			if (fAlpha <= 0)
			{
				fAlpha = 0.0f;
			}
			else
			{
				fAlpha -= GetSecPerFrame;
			}
			MySceen->Frame();
		}
		else if (ChangeSceenMaxTime < ChangeSceenTime)
		{
			MyOldSceen->Release();
			ChangeSceenTime = 0;
			bChange = false;
			fAlpha = 0;
		}
	}
	else
	{
		if (!MySceen->Frame())
		{
			return false; 
		}
	}
	return true;
}
bool SssSceenManeger::Render()
{
	if (bChange)
	{
		BLENDFUNCTION Blend;
		Blend.BlendOp = AC_SRC_OVER;
		Blend.BlendFlags = 0;
		Blend.AlphaFormat = 0;
		Blend.SourceConstantAlpha = fAlpha * 255;
	
		if (ChangeSceenTime < ChangeSceenMaxTime / 2)
		{
			MyOldSceen->Render();
			AlphaBlend(MyOffScreen, 0, 0, 1024, 768, MyBlendScreen, 0, 0, 1024, 768, Blend);
		}
		else if (ChangeSceenMaxTime / 2 < ChangeSceenTime &&  ChangeSceenTime < ChangeSceenMaxTime)
		{
			MySceen->Render();
			AlphaBlend(MyOffScreen, 0, 0, 1024, 768, MyBlendScreen, 0, 0, 1024, 768, Blend);
		}
	}
	else
	{
		MySceen->Render();
	}
	return true;
}
bool SssSceenManeger::Release()
{
	for (auto Del : MySceenList)
	{
		Del.second->Release();
		delete Del.second;
	}
	MySceenList.clear();
	return true;
}
bool SssSceenManeger::ChangeSceen(int iState)
{
	MyOldSceen = MySceen;
	MySceen = MySceenList.find(iState)->second;
	MySceen->Init(MyWindowScreen, MyOffScreen);
	bChange = true;
	return true;
}

