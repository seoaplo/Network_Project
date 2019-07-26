#include "SssPlayer.h"

#pragma region PlayerDown
bool SssPlayerDown::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	return true;
}
bool SssPlayerDown::Frame()
{
	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerDown::Render()
{
	if (pParent->CheckArrowkey == 'A')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
	}
	else if (pParent->CheckArrowkey == 'D')
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	else
	{
		if (pParent->BeforeArrowkey == 'A')
		{
			SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
		}
		else
		{
			SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
		}
	}
	return true;
}
bool SssPlayerDown::Release()
{
	return true;
}
bool SssPlayerDown::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion 
