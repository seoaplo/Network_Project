#include "SssPlayer.h"

#pragma region PlayerJump
bool SssPlayerJump::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	fJumpPower = 0.0f;
	return true;
}
bool SssPlayerJump::Frame()
{
	pParent->bGround = false;
	if (!pParent->bCeiling)
	{
		pParent->fJumpPower -= pParent->fGravity * GetSecPerFrame;
		pParent->MyRealPos->y -= pParent->fJumpPower * GetSecPerFrame;
	}
	float Speed;
	if (pParent->DashPower)
	{
		Speed = pParent->iDashSpeed;
	}
	else
	{
		Speed = pParent->iSpeed;
	}
	if (pParent->fJumpPower <= 1.0f)
	{
		bJump = false;
	}
	if (pParent->CheckArrowkey == 'A' && !pParent->bStopLeft)
	{
		pParent->MyRealPos->x -= Speed * GetSecPerFrame;
	}
	else if (pParent->CheckArrowkey == 'D' && !pParent->bStopRight)
	{
		pParent->MyRealPos->x += Speed * GetSecPerFrame;
	}
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	SpriteImege->Frame();
	return true;
}
bool SssPlayerJump::Render()
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
bool SssPlayerJump::Release()
{
	return true;
}
bool SssPlayerJump::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion 
