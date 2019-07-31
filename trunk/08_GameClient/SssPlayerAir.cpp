#include "SssPlayer.h"


#pragma region PlayerAir
bool SssPlayerAir::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	return true;
}
bool SssPlayerAir::Frame()
{
	float Speed;
	Speed = pParent->iSpeed;
	if (pParent->fJumpPower > 1.0f)
	{
		pParent->fJumpPower -= pParent->fJumpPower;
	}
	pParent->fJumpPower -= pParent->fGravity * GetSecPerFrame;

	pParent->MyRealPos->y -= max(-3 , pParent->fJumpPower * GetSecPerFrame);
	if (pParent->CheckArrowkey == 'A' && !bStopLeft)
	{
		pParent->MyRealPos->x -= Speed * GetSecPerFrame;
	}
	if (pParent->CheckArrowkey == 'D' && !bStopRight)
	{
		pParent->MyRealPos->x += Speed * GetSecPerFrame;
	}
	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerAir::Render()
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
bool SssPlayerAir::Release()
{
	return true;
}
bool SssPlayerAir::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion 
