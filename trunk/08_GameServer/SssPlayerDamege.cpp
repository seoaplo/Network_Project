#include "SssPlayer.h"

bool SssPlayerDamege::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	iSoundIndex = SingleSoundManeger.Load("../Data/Damege.wav");
	fSoundSize = 0;
	fSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;
	return true;
}
bool SssPlayerDamege::Frame()
{
	if (pParent->DamegeTime < pParent->DamegeMaxTime)
	{
		pParent->DamegeTime += GetSecPerFrame;
	}
	else
	{
		pParent->bDamege = false;
		pParent->bShield = true;
	}

	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	return true;
}
bool SssPlayerDamege::Render()
{
	if (fSoundSize < fSoundMaxSize)
	{
		SingleSoundManeger.PlayEffect(iSoundIndex);
		fSoundSize += GetSecPerFrame;
	}
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
bool SssPlayerDamege::Release()
{
	return true;
}
bool SssPlayerDamege::CheckEvent(SssObject& TargetObject)
{
	return true;
}