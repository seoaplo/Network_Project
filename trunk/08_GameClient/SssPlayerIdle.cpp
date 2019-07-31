#include "SssPlayer.h"


#pragma region PlayerIdle
bool SssPlayerIdle::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	return true;
}
bool SssPlayerIdle::Frame()
{
	if (pParent->BeforeArrowkey == 'A')
	{
		Right = false;
	}
	else if (pParent->BeforeArrowkey == 'D')
	{
		Right = true;
	}
	else
	{
		Right = true;
	}
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	SpriteImege->Frame();
	return true;
}
bool SssPlayerIdle::Render()
{
	if (pParent->BeforeArrowkey == 'D')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	else if (pParent->BeforeArrowkey == 'A')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
	}
	return true;
}
bool SssPlayerIdle::Release()
{
	return true;
}
bool SssPlayerIdle::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion
