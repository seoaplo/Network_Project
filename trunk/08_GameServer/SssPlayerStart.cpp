#include "SssPlayer.h"

bool SssPlayerStart::Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider)
{
	pParent = Parent;
	MyOffScreen = OffScreen;
	MyRealPos = Pos;
	MyCollider = TargetCollider;
	int Key =  SingleSpriteManeger.GetKey(L"RectStartBeam");
	Teleport = SingleSpriteManeger.GetSprite(Key);
	Teleport->Init();
	iSoundIndex = SingleSoundManeger.Load("../../../data/StartTelePort.wav");
	fSoundSize = 0;
	fSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;
	ArrowKey = 'D';
	return true;
}
bool SssPlayerStart::Frame()
{
	float fChangeTime = 0.0f;
	if (pParent->bTeleport)
	{
		fChangeTime = 100 * 3 * GetSecPerFrame;
		pParent->MyRealPos->y += min(7, fChangeTime);
			
	}
	else
	{
		SpriteImege->Frame();
		pParent->fStartMotionTime += GetSecPerFrame;
	}
	
	pParent->MyPos.x = pParent->MyRealPos->x;
	pParent->MyPos.y = pParent->MyRealPos->y;
	if (pParent->RegenPoint.y <= pParent->MyPos.y)
	{
		bReady = true;
	}
	
	return true;
}
bool SssPlayerStart::Render()
{
	if (fSoundSize < fSoundMaxSize)
	{
		SingleSoundManeger.Play(iSoundIndex, FMOD_DEFAULT);
		fSoundSize += GetSecPerFrame;
	}
	if (((pParent->fStartMotionMaxTime / 17) * 8) > pParent->fStartMotionTime)
	{
		pParent->MyPos.x += 6;
		pParent->MyPos.y -= 20;
	}
	else
	{
		pParent->MyPos.y += 11;
		pParent->MyPos.y -= 20;
	}
	if (!pParent->bTeleport)
	{
		if (ArrowKey == 'A')
		{
			SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_WidthMirror);
		}
		else if (ArrowKey == 'D')
		{
			SpriteImege->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
		}
	}
	else
	{
		Teleport->Draw(MyOffScreen, pParent->CameraPos, pParent->iPlayerSize, IDO_RECT);
	}
	return true;
}
bool SssPlayerStart::Release()
{
	return true;
}
bool SssPlayerStart::CheckEvent(SssObject& TargetObject)
{
	return true;
}