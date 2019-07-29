#include "SssPlayer.h"


#pragma region PlayerDashBreak
bool SssPlayerDashBreak::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	iSoundIndex = SingleSoundManeger.Load("../../../data/Break.wav");
	fSoundSize = 0;
	fSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;
	return true;
}
bool SssPlayerDashBreak::Frame()
{
	if (fSoundSize < fSoundMaxSize)
	{
		SingleSoundManeger.PlayEffect(iSoundIndex);
		fSoundSize += GetSecPerFrame;
	}
	if (pParent->fBreakTime >= 0)
	{
		if (pParent->BeforeArrowkey == 'D')
		{
			DrawOption = IDO_RECT;
		}
		else if (pParent->BeforeArrowkey == 'A')
		{
			DrawOption = IDO_WidthMirror;
		}
	}
	pParent->fBreakTime += GetSecPerFrame;

	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerDashBreak::Render()
{
	SpriteImege->Draw(pParent->MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, DrawOption);
	return true;
}
bool SssPlayerDashBreak::Release()
{
	return true;
}
bool SssPlayerDashBreak::CheckEvent(SssObject& TargetObject)
{
	return true;
}
#pragma endregion