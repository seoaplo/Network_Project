#include "SssPlayer.h"

bool SssPlayerVictory::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	int Key = SingleSpriteManeger.GetKey(L"RectVictoryTeleport");
	Teleport = SingleSpriteManeger.GetSprite(Key);
	fTeleportMotionTime = 0.0f;
	fTeleportMotionMaxTime = 0.3f;
	Teleport->SetDrawTime(fTeleportMotionMaxTime);
	iSoundIndex = SingleSoundManeger.Load("../../../data/VictoryTelePort.wav");
	fSoundSize = 0;
	fSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;
	return true;
}
bool SssPlayerVictory::Frame()
{
	if(pParent->fVictoryMotionTime < pParent->fVictoryMotionMaxTime)
	{
		SpriteImege->Frame();
		pParent->fVictoryMotionTime += GetSecPerFrame;
	}
	else if(fTeleportMotionMaxTime > fTeleportMotionTime)
	{
		Teleport->Frame();
		fTeleportMotionTime += GetSecPerFrame;
	}
	else
	{
		pParent->MyRealPos->y -= 100 * 3 * GetSecPerFrame;
	}

	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	pParent->MyPos.y -= 20;

	return true;
}
bool SssPlayerVictory::Render()
{
	if (fSoundSize < fSoundMaxSize && pParent->fVictoryMotionTime > pParent->fVictoryMotionMaxTime)
	{
		SingleSoundManeger.Play(iSoundIndex, FMOD_DEFAULT);
		fSoundSize += GetSecPerFrame;
	}
	if (pParent->fVictoryMotionTime < pParent->fVictoryMotionMaxTime)
		SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	else
		Teleport->Draw(pParent->MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	return true;
}    
bool SssPlayerVictory::Release()
{
	return true;
}
bool SssPlayerVictory::CheckEvent(SssObject& TargetObject)
{
	return true;
}