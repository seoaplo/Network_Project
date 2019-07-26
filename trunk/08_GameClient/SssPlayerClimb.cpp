#include "SssPlayer.h"

#pragma region PlayerClimb
bool SssPlayerClimb::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	iSoundIndex = SingleSoundManeger.Load("../Data/Climb.wav");
	fSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;
	fSoundSize = 0.0f;
	COLORREF Color = RGB(29, 112, 189);
	return true;
}
bool SssPlayerClimb::Frame()
{
	pParent->MyRealPos->y += (pParent->fGravity / 3)* GetSecPerFrame;
	pParent->fJumpPower = 0.0f;
	pParent->DashPower = false;
	if (pParent->CheckArrowkey == 'A')
	{
		if (!pParent->bStopLeft)
			pParent->MyRealPos->x -= 1;
	}
	else if (pParent->CheckArrowkey == 'D')
	{
		if (!pParent->bStopRight)
			pParent->MyRealPos->x += 1;
	}
	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerClimb::Render()
{
	if (fSoundMaxSize > fSoundSize)
	{
		SingleSoundManeger.PlayEffect(iSoundIndex);
		fSoundSize += GetSecPerFrame;
	}
	if (pParent->bStopRight)
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	if (pParent->bStopLeft)
	{
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
	}
	return true;
}
bool SssPlayerClimb::Release()
{
	return true;
}
bool SssPlayerClimb::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion