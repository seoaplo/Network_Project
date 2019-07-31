#include "SssPlayer.h"

#pragma region PlayerRun
bool SssPlayerRun::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	return true;
}
bool SssPlayerRun::Frame()
{
	if (pParent->CheckArrowkey == 'A')
	{
		if (pParent->bStopRight)
		{
			pParent->MyRealPos->x -= 1;
		}
		else
		{
			pParent->MyRealPos->x -= pParent->iSpeed * GetSecPerFrame;
		}
	}
	else if(pParent->CheckArrowkey == 'D')
	{
		if (pParent->bStopLeft)
		{
			pParent->MyRealPos->x += 1;
		}
		else
		{
			pParent->MyRealPos->x += pParent->iSpeed * GetSecPerFrame;
		}
	}
	if (pParent->BeforeArrowkey != pParent->CheckArrowkey)
	{
		SpriteImege->Init();
	}
	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerRun::Render()
{
	if (pParent->CheckArrowkey == 'D')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	else if(pParent->CheckArrowkey == 'A')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
	}
	return true;
}
bool SssPlayerRun::Release()
{
	return true;
}
bool SssPlayerRun::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion