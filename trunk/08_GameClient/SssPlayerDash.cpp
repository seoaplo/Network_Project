#include "SssPlayer.h"

#pragma region PlayerDash
bool SssPlayerDash::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	MaxDashTime = 1.0f;
	COLORREF Color = RGB(29, 112, 189);
	
	return true;
}
bool SssPlayerDash::Frame()
{
	pParent->DashTime += GetSecPerFrame;
	DashPower = true;
	if (pParent->CheckArrowkey == 'A')
	{
		if (!pParent->bStopLeft)
		{
			pParent->MyRealPos->x -= pParent->iDashSpeed * GetSecPerFrame;
		}
	}
	else if (pParent->CheckArrowkey == 'D')
	{
		if (!pParent->bStopRight)
		{
			pParent->MyRealPos->x += pParent->iDashSpeed * GetSecPerFrame;
		}
	}

	if (pParent->BeforeArrowkey != pParent->CheckArrowkey)
	{
		SpriteImege->Init();
		pParent->DashTime = 0;
		pParent->bDash = false;
	}

	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerDash::Render()
{
	if (fSoundSize < fSoundMaxSize)
	{
		SingleSoundManeger.PlayEffect(iSoundIndex);
		fSoundSize += GetSecPerFrame;
	}

	if (pParent->CheckArrowkey == 'D')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	else if (pParent->CheckArrowkey == 'A')
	{
		
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
	}
	return true;
}
bool SssPlayerDash::Release()
{
	return true;
}
bool SssPlayerDash::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion
