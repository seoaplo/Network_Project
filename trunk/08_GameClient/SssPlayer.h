#pragma once
#include "Game/Ssslibheader.h"
#include "SssFSM.h"
#include "SssEffect.h"

enum PlayerState
{
	Player_Start = 0,
	Player_Idle,
	Player_Run,
	Player_Dash,
	Player_DashBreak,
	Player_Jump,
	Player_Air,
	Player_Down,
	Player_Victory,
	Player_Climb,
	Player_ClimbJump,
	Player_Damege,
	Player_Death,
	Player_StateSize
};
enum PlayerEvent
{
	pEvent_Start = 0,
	pEvent_Idle,
	pEvent_Run,
	pEvent_Dash,
	pEvent_DashBreak,
	pEvent_Jump,
	pEvent_Air,
	pEvent_Down,
	pEvent_Victory,
	pEvent_Climb,
	pEvent_ClimbJump,
	pEvent_Damege,
	pEvent_Death,
	pEvent_StateSize
};

class SssPlayer : public SssObject
{
public:
	SssPlayer* pParent;
	std::map <DWORD, SssPlayer*> MyStateList;
	SssFSM MyFSM;
	SssPlayer* MyControlState;
	DWORD MyState;
	DWORD MybeforeState;
	SssPoint* MyRealPos;
	SssEffect MyEffect;
	float iPlayerSize;
	POINT CameraPos;

	DWORD m_KeyState[MAX_PATH];
public:
	int iSpeed;
	int iDashSpeed;
	int BeforeArrowkey;
	int CheckArrowkey;
public:
	float DashTime;
	bool bDash;
	bool DashPower;
	float fBreakTime;
	float fMaxBreakTime;
public:
	float fJumpPower;
	float fMaxJumpPower;
	bool bJump;
	float fGravity;
	bool bGround;
	float fDownTime;
	float fMaxDownTime;
public:
	bool bStopLeft;
	bool bStopRight;
	bool bClimb;
	float fClimbJumpTime;
	float fClimbJumpMaxTime;
	bool bClimbJumpRight;
	bool bClimbJumpleft;
	bool bCeiling;
public:
	bool DemegeDraw;
	float DamegeTime;
	float DamegeMaxTime;
	bool	bDamege;
	bool bShield;
public:
	float fStartMotionTime;
	float fStartMotionMaxTime;
	bool  bReady;
	bool bTeleport;
	POINT RegenPoint;
public:
	float fVictoryMotionTime;
	float fVictoryMotionMaxTime;
	bool  bVictory;
private:
	float fJumpTime;
	float fJumpMaxTime;
private:
	float fShiledTime;
	float fShieldMaxTime;
protected:
	float fSoundMaxSize;
	float fSoundSize;
private:
	int iDashSound;
	float iDashSoundSize;
	float iDashSoundMaxSize;
private:
	int iDownEffectSound;
	float fDownEffectSoundSize;
	float fDownEffectSoundMaxSize;
private:
	int iJumpEffectSound;
	int iJumpEffectSound2;
	float  iJumpEffectSoundSize;
	float  iJumpEffectSoundMaxSize;
private:
	float ClimbEffectTime;
	float ClimbEffectMaxTime;
	SssEffect ClimbEffect;
private:
	float ClimbJumpEffectTime;
	float ClimbJumpEffectMaxTime;
	SssEffect ClimbJumpEffect;
private:
	float DashEffectTime;
	float DashEffectMaxTime;
	SssEffect DashEffect;
	SssSprite* DashEffectSprite;
private:
	RECT CheckWallRect;
	POINT MyBeforePos;
	float CheckBeforeMaxTime;
	float CheckBeforeTime;
private:
	bool CheckBlock;
	bool bCheckStop;
private:
	int MyHP;
	bool GodMode;
	bool bDeatth;
	float bDeathTime;
	float bDeathMaxTime;
public:
	void SetKeyState(DWORD Key, DWORD State)
	{
		m_KeyState[Key] = State;
	}
	void SetReady()
	{
		bReady = true;
	}
	bool GetDeath()
	{
		return bDeatth;
	}
	void SetVictory()
	{
		bVictory = true;
	}
public:
	virtual bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	virtual bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider) { return true; }
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayer();
	~SssPlayer();
};

class SssPlayerIdle : public SssPlayer
{
public:
	bool Right;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerIdle() { Right = true; };
	~SssPlayerIdle() {};
};

class SssPlayerRun : public SssPlayer
{
public:

public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerRun() {  };
	~SssPlayerRun() {};
};

class SssPlayerDash : public SssPlayer
{
public:
	float MaxDashTime;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerDash() {};
	~SssPlayerDash() {};
};

class SssPlayerDashBreak : public SssPlayer
{
public:
	int DrawOption;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerDashBreak() {  };
	~SssPlayerDashBreak() {};
};

class SssPlayerJump : public SssPlayer
{
private:
	int iJumpSound;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerJump() {  };
	~SssPlayerJump() {};
};

class SssPlayerAir : public SssPlayer
{
public:

public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerAir() {  };
	~SssPlayerAir() {};
};

class SssPlayerDown : public SssPlayer
{
public:
	
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerDown() {  };
	~SssPlayerDown() {};
};


class SssPlayerClimb : public SssPlayer
{
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerClimb() {  };
	~SssPlayerClimb() {};
};

class SssPlayerClimbJump : public SssPlayer
{
private:
	int iClimbJumpSound;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerClimbJump() {  };
	~SssPlayerClimbJump() {};
};

class SssPlayerDamege : public SssPlayer
{
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerDamege() {  };
	~SssPlayerDamege() {};
};

class SssPlayerStart : public SssPlayer
{
private:
	SssSprite* Teleport;
	int ArrowKey;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerStart() {  };
	~SssPlayerStart() {};
};

class SssPlayerVictory : public SssPlayer
{
public:
	SssSprite* Teleport;
	float fTeleportMotionTime;
	float fTeleportMotionMaxTime;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerVictory() {  };
	~SssPlayerVictory() {};
};

class SssPlayerDeath : public SssPlayer
{
	bool bSoundPlay;
	int ArrowKey;
	float DeathTIme;
	float DeathMaxTIme;
public:
	bool Init(SssPlayer* Parent, HDC OffScreen, SssPoint* Pos, HDC WindowDC, SssCollider* TargetCollider);
	bool Frame();
	bool Render();
	bool Release();
public:
	SssPlayerDeath() {  };
	~SssPlayerDeath() {};
};