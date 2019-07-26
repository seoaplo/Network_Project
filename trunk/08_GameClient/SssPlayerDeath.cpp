#include "SssPlayer.h"

bool SssPlayerDeath::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	int Key = SingleSpriteManeger.GetKey(L"RectDeath");
	iSoundIndex = SingleSoundManeger.Load("../Data/PlayerDeath.wav");
	bSoundPlay = false;
	ArrowKey = 'D';
	DeathTIme = 0.0f;
	DeathMaxTIme = 0.5f;
	return true;
}
bool SssPlayerDeath::Frame()
{
	if (!bSoundPlay)
	{
		ArrowKey = pParent->CheckArrowkey;
		SingleSoundManeger.PlayEffect(iSoundIndex);
		bSoundPlay = true;
	}
	DeathTIme += GetSecPerFrame;
	SpriteImege->Frame();
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;

	return true;
}
bool SssPlayerDeath::Render()
{
	if (DeathTIme < DeathMaxTIme)
	{
		if (ArrowKey == 'D')
			SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
		else
		{
			SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
		}
	}
	
	return true;
}
bool SssPlayerDeath::Release()
{
	return true;
}
