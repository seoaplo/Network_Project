#include "SssPlayer.h"

#pragma region PlayerClimbJump
bool SssPlayerClimbJump::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	iSoundIndex = SingleSoundManeger.Load("../../../data/ClimbJump.wav");
	fSoundSize = 0;
	fSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;
	return true;
}
bool SssPlayerClimbJump::Frame()
{
	//fJumpPower -= fGravity * GetSecPerFrame;
	if(!pParent->bCeiling)
		pParent->MyRealPos->y -= pParent->fMaxJumpPower  * GetSecPerFrame;

	pParent->fClimbJumpTime += GetSecPerFrame;
	float Speed;
	if (pParent->fClimbJumpTime >= pParent->fClimbJumpMaxTime)
	{
		pParent->bClimbJumpRight = false;
		pParent->bClimbJumpleft = false;
	}
	if (pParent->DashPower)
	{
		Speed = pParent->iDashSpeed;
	}
	else
	{
		Speed = pParent->iSpeed;
	}
	if (pParent->bClimbJumpRight)
	{
		pParent->MyRealPos->x -= Speed * GetSecPerFrame;
	}
	else if (pParent->bClimbJumpleft)
	{
		pParent->MyRealPos->x += Speed * GetSecPerFrame;
	}
	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerClimbJump::Render()
{
 	if (fSoundSize < fSoundMaxSize)
	{
		SingleSoundManeger.PlayEffect(iSoundIndex);
	//	SingleSoundManeger.PlayEffect(iClimbJumpSound);
		fSoundSize += GetSecPerFrame;
	}
	if (pParent->bClimbJumpRight)
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	else if (pParent->bClimbJumpleft)
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
	}
	return true;
}
bool SssPlayerClimbJump::Release()
{
	return true;
}
bool SssPlayerClimbJump::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion