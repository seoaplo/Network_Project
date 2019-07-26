#include "SssPlayer.h"



bool SssPlayer::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
#pragma region Create

	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 500, 500);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	pParent = nullptr;
	MyRealPos = new SssPoint;
	MyRealPos->x = TargetPos.x;
	MyRealPos->y = 0;
	MyPos.x = TargetPos.x;
	MyPos.y = 0;
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 39;
	MyRect.bottom = 58;

	MyCollider = &CollisionManeger.AddCollider(MyPos, MyRect, this, Col_Rect);

	int SpriteNumber;
	SssSprite* MySprite;
	COLORREF Color = RGB(29, 112, 189);

	ObjectName = L"PlayerObject";
	AttackerPoint = MyPos;
	MyAttacker.Init(MyOffScreen, AttackerPoint, WindowDC);

	CameraPos.x = 250;
	CameraPos.y = 250;
	
#pragma endregion 

#pragma region StateValiableInit

	iPlayerSize = 2;

	iSpeed = 300;
	iDashSpeed = 600;

	bGround = false;
	bJump = false;
	fJumpPower = 0.0f;
	fMaxJumpPower = 500.0f;
	fJumpTime = 0.0f;
	fJumpMaxTime = 1.0f;

	fGravity = 500.0f;
	fDownTime = 0.1f;
	fMaxDownTime = 0.1f;

	DashPower = false;
	fBreakTime = 0.0f;
	fMaxBreakTime = 0.3f;

	fClimbJumpTime = 0.0f;
	fClimbJumpMaxTime = 0.25f;

	DamegeTime = 0.0f;
	DamegeMaxTime = 0.5;
	bDamege = false;
	DemegeDraw = false;

	bShield = false;
	fShieldMaxTime = 1.0f;
	fShiledTime = 0.0f;

	fStartMotionTime = 0.0f;
	fStartMotionMaxTime = 1.0f;
	bReady = false;
	RegenPoint = TargetPos;

	fVictoryMotionTime = 0.0f;
	fVictoryMotionMaxTime = 0.7f;
	bVictory = false;

	bCeiling = false;
	bStopRight = false;
	bStopLeft = false;
	bClimbJumpRight = false;
	bClimbJumpleft = false;
	bClimb = false;
	bGround = false;
	CheckBlock = false;
	bCheckStop = false;

	CheckBeforeMaxTime = 0.1f;
	CheckBeforeTime = CheckBeforeMaxTime;

	MyBeforePos.x = MyPos.x;
	MyBeforePos.y = MyPos.y - 30;

	MyHP = 5;
	GodMode = false;
	bDeatth = false;
	bDeathTime = 0.0f;
	bDeathMaxTime = 2.0f;

	bTeleport = true;
	
#pragma endregion 

#pragma region State
#pragma region IdleInit
	SpriteNumber = SingleSpriteManeger.CreateSprite
	(L"../Data/PlayerRect2.txt", L"../Data/Player2.bmp", L"RectIdle", Color, WindowDC, 1.5);
	SssPlayer* NewState = new SssPlayerIdle;
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->Init();
	MyStateList.insert(std::make_pair(Player_Idle, NewState));
#pragma endregion

#pragma region RunInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectRun");
	NewState = new SssPlayerRun;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(0.7f);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Run, NewState));
#pragma endregion 

#pragma region DashInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectDash");
	NewState = new SssPlayerDash;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(0.2f);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Dash, NewState));
#pragma endregion 

#pragma region DashBreakInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectDashBreak");
	NewState = new SssPlayerDashBreak;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(fMaxBreakTime);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_DashBreak, NewState));
#pragma endregion 

#pragma region JumpInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectJump");
	NewState = new SssPlayerJump;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(0.3f);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Jump, NewState));
#pragma endregion 

#pragma region AirInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectAir");
	NewState = new SssPlayerAir;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(0.3f);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Air, NewState));
#pragma endregion 

#pragma region DownInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectDown");
	NewState = new SssPlayerDown;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(fMaxDownTime);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Down, NewState));
#pragma endregion

#pragma region ClimbInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectClimb");
	NewState = new SssPlayerClimb;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(0.3f);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Climb, NewState));
#pragma endregion 

#pragma region ClimbJumpInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectClimbJump");
	NewState = new SssPlayerClimbJump;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(fClimbJumpMaxTime);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_ClimbJump, NewState));
#pragma endregion 

#pragma region DamegeInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectDamege");
	NewState = new SssPlayerDamege;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(DamegeMaxTime);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Damege, NewState));
#pragma endregion 

#pragma region VictoryInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectVictory");
	NewState = new SssPlayerVictory;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(fVictoryMotionMaxTime - 0.3f);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Victory, NewState));
#pragma endregion 

#pragma region StartInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectStart");
	NewState = new SssPlayerStart;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(fStartMotionMaxTime);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Start, NewState));
#pragma endregion 

#pragma region DeathInit
	SpriteNumber = SingleSpriteManeger.GetKey(L"RectDeath");
	NewState = new SssPlayerDeath;
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege = SingleSpriteManeger.GetSprite(SpriteNumber);
	NewState->SpriteImege->SetDrawTime(fStartMotionMaxTime);
	NewState->SpriteImege->Init();
	NewState->Init(this, MyScreen, MyRealPos, WindowDC, MyCollider);
	MyStateList.insert(std::make_pair(Player_Death, NewState));
#pragma endregion 


#pragma region PlayerFSM

	for (int iFirstCount = 0; iFirstCount < Player_StateSize; iFirstCount++)
	{
		for (int iSecondCount = 0; iSecondCount < pEvent_StateSize; iSecondCount++)
		{
			MyFSM.CreateFSM(iFirstCount, iSecondCount, iSecondCount);
		}
	}
#pragma endregion

	MyState = Player_Start;
	MybeforeState = Player_Start;
	BeforeArrowkey = 'D';
	std::map<DWORD, SssPlayer*>::iterator SetControlState = MyStateList.find(Player_Start);
	MyControlState = SetControlState->second;

	iDashSound = SingleSoundManeger.Load("../Data/Dash.wav");
	iDashSoundSize = 0;
	iDashSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iSoundIndex)) / 1000.0f) / 60.0f;

	iDownEffectSound = SingleSoundManeger.Load("../Data/Down.wav");
	fDownEffectSoundSize = 0;
	fDownEffectSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iDownEffectSound)) / 1000.0f) / 60.0f;

	iJumpEffectSound = SingleSoundManeger.Load("../Data/Jump.wav");
	iJumpEffectSound2 = SingleSoundManeger.Load("../Data/Jump2.wav");
	iJumpEffectSoundMaxSize = ((SingleSoundManeger.GetSoundSize(iJumpEffectSound)) / 1000.0f) / 60.0f;

#pragma region Effect
	ClimbEffectMaxTime = 0.3f;
	ClimbEffectTime = 0.0f;
	ClimbEffect.Init(OffScreen, MyPos, WindowDC, L"../Data/Player_Effect.bmp", L"RectEffectClimb", Color, L"../Data/PlayerEffect1.txt", NULL, ClimbEffectMaxTime);

	ClimbJumpEffectTime = 0.3f;
	ClimbJumpEffectMaxTime = 0.0f;
	ClimbJumpEffect.Init(OffScreen, MyPos, WindowDC, L"../Data/Player_Effect.bmp", L"RectEffectClimbJump", Color, L"../Data/PlayerEffect1.txt", "../Data/ClmibJump2.wav", ClimbEffectMaxTime);


	DashEffectTime = 0.3f;
	DashEffectMaxTime = 0.0f;
	DashEffect.Init(OffScreen, MyPos, WindowDC, L"../Data/Player_Effect.bmp", L"RectEffectDash2", Color, L"../Data/PlayerEffect1.txt", NULL, ClimbEffectMaxTime);

	int Key = SingleSpriteManeger.CreateSprite
	(L"../Data/PlayerEffect1.txt", L"../Data/Player_Effect.bmp", L"RectEffectDash1", Color, WindowDC, 1.5);
	DashEffectSprite = SingleSpriteManeger.GetSprite(Key);
	DashEffectSprite->SetDrawTime(0.3f);
#pragma endregion

#pragma endregion 
	return true;
}
bool SssPlayer::Frame()
{
	if (MyState != Player_Start && bReady)
	{
		MyState = MyFSM.GetState(MyState, Player_Idle);

		std::map<DWORD, SssPlayer*>::iterator SetControlState = MyStateList.find(MyState);
		MyControlState = SetControlState->second;

		MyCollider->SetRect(MyRect);

		MyControlState->Frame();
		MyPos.x = MyRealPos->x;
		MyPos.y = MyRealPos->y;

		return true;
	}

	if (!CheckBlock)
	{
		bStopRight = false;
		bStopLeft = false;
		bClimb = false;
		bGround = false;
		bCeiling = false;
	}
	if (!bCheckStop)
	{
		bStopRight = false;
		bStopLeft = false;
		bClimb = false;
	}
	if (MyState == Player_Dash)
	{
		bGround = true;
	}
	if (MyHP <= 0)
	{
		bDeatth = true;
		bDeathTime += GetSecPerFrame;
	}
	
	if (m_KeyState[VK_CONTROL] == Key_Push)
	{
		GodMode = !GodMode;
	}

	if (bShield == true)
	{
		if (fShiledTime < fShieldMaxTime)
		{
			DemegeDraw = !DemegeDraw;
			fShiledTime += GetSecPerFrame;
		}
		else
		{
			bShield = false;
			DemegeDraw = false;
			fShiledTime = 0;
			DamegeTime = 0;
		}
	}
#pragma region Ground
	if (m_KeyState['A'] == Key_Push ||
		m_KeyState['A'] == Key_Hold)
	{
		CheckArrowkey = 'A';
		if (!bStopLeft)
		{
			MyState = MyFSM.GetState(MyState, pEvent_Run);

		}
		else
		{
			MyState = MyFSM.GetState(MyState, pEvent_Idle);
		}
	}
	else if (m_KeyState['D'] == Key_Push ||
		m_KeyState['D'] == Key_Hold)
	{
		CheckArrowkey = 'D';
		if (!bStopRight)
		{
			MyState = MyFSM.GetState(MyState, pEvent_Run);
		}
		else
		{
			MyState = MyFSM.GetState(MyState, pEvent_Idle);
		}
	}
	else
	{
		CheckArrowkey = 0;
	}

	if (!bStopLeft && !bStopRight)
	{
		if (m_KeyState[VK_SHIFT] == Key_Push)
		{
			POINT EffectPos = MyPos;
			
			if (CheckArrowkey == 'D')
			{
				EffectPos.x -= 10;
				DashEffect.SetDrawData(EffectPos, 2, IDO_RECT);
			}
			else if(CheckArrowkey == 'A')
			{
				EffectPos.x += 10;
				DashEffect.SetDrawData(EffectPos, 2, IDO_WidthMirror);
			}
			
			bDash = true;
			DashTime = 0;
			MyState = MyFSM.GetState(MyState, pEvent_Dash);

			SingleSoundManeger.PlayEffect(iDashSound);
		}
		else if(CheckArrowkey != BeforeArrowkey || MybeforeState != Player_Dash)
		{
			bDash = false;
			DashEffectSprite->Init();
		}
		else if (m_KeyState[VK_SHIFT] == Key_Hold && bDash && DashTime < 1.5)
		{
			DashTime += GetSecPerFrame;
			MyState = MyFSM.GetState(MyState, pEvent_Dash);
		}
		else
		{
			DashTime = 0;
			SingleSoundManeger.Stop(iDashSound);
			DashEffect.Release();
		}
	}

	if (CheckArrowkey == 0)
	{
		MyState = MyFSM.GetState(MyState, pEvent_Idle);

		SingleSoundManeger.Stop(iDashSound);
		DashEffect.Release();
	}

	if (MybeforeState == Player_Dash && MyState == Player_Idle)
	{
		fBreakTime = 0;
		MyState = MyFSM.GetState(MyState, pEvent_DashBreak);

		SingleSoundManeger.Stop(iDashSound);
		DashEffect.Release();
	}
	else if (fBreakTime < fMaxBreakTime && MybeforeState == Player_DashBreak && MyState != Player_Dash)
	{
		SingleSoundManeger.Stop(iDashSound);
		DashEffect.Release();
		MyState = MyFSM.GetState(MyState, pEvent_DashBreak);
	}
#pragma endregion
	
#pragma region Jump
	if (m_KeyState[VK_SPACE] == Key_Push && bGround && !bJump && !bCeiling)
	{
		SingleSoundManeger.Stop(iDashSound);
		DashEffect.Release();
		if (iJumpEffectSoundSize < iJumpEffectSoundMaxSize)
		{
			SingleSoundManeger.PlayEffect(iJumpEffectSound);
			SingleSoundManeger.PlayEffect(iJumpEffectSound2);
			fSoundSize += GetSecPerFrame;
		}
		MyState = MyFSM.GetState(MyState, pEvent_Jump);

 		bGround = false;
		fJumpTime = 0.0f;
		bJump = true;
		fJumpPower = fMaxJumpPower;
	}
	else if(bJump && m_KeyState[VK_SPACE] == Key_Hold
		&& m_KeyState[VK_SPACE] != Key_Push && !bCeiling
		&& fJumpTime < fJumpMaxTime)
	{
		fSoundSize += GetSecPerFrame;
		fJumpTime += GetSecPerFrame;
		MyState = MyFSM.GetState(MyState, pEvent_Jump);

		fDownTime = 0;
		fDownEffectSoundSize = 0;
	}
	else if (!bGround)
	{
		fJumpTime = 0.0f;
		bGround = false;
		bJump = false;
		MyState = MyFSM.GetState(MyState, pEvent_Air);

	}
	else if (fDownTime < fMaxDownTime )
	{
		if (fDownEffectSoundSize < fDownEffectSoundMaxSize && fStartMotionTime > fStartMotionMaxTime)
		{
			SingleSoundManeger.PlayEffect(iDownEffectSound);
			fDownEffectSoundSize += GetSecPerFrame;
		}
		fDownTime += GetSecPerFrame;
		if (CheckArrowkey == 0)
		{
			MyState = MyFSM.GetState(MyState, pEvent_Down);

		}
	}
#pragma endregion

	
#pragma region Climb
	if (bClimb && !bGround && CheckArrowkey != 0 && fJumpTime >= 0.2f)
	{
		MyState = MyFSM.GetState(MyState, pEvent_Climb);

		if (ClimbEffectTime >= 0.1)
		{
			SingleSoundManeger.Stop(iDashSound);
			POINT ClimbEffectPos = MyPos;
			ClimbEffectPos.y += 30;
			if (bStopLeft)
			{
 				ClimbEffectPos.x -= 20;
				ClimbEffect.SetDrawData(ClimbEffectPos, 2, IDO_WidthMirror);
			}
			else if (bStopRight)
			{
				ClimbEffectPos.x += 20;
				ClimbEffect.SetDrawData(ClimbEffectPos, 2, IDO_RECT);
			}
			ClimbEffectTime = 0.0f;
		}
		else
		{
			ClimbEffectTime += GetSecPerFrame;
		}
	}
	else
	{
		ClimbEffect.Release();
	}
	if (m_KeyState[VK_SPACE] == Key_Push && !bGround && bClimb)
	{
		POINT EffectPos = MyPos;
		EffectPos.y += 25;
		fClimbJumpTime = 0;
		MyState = MyFSM.GetState(MyState, pEvent_ClimbJump);

		DashPower = false;
		ClimbJumpEffect.SetDrawData(EffectPos, 2, IDO_RECT);
		if (m_KeyState[VK_SHIFT] == Key_Push ||
			m_KeyState[VK_SHIFT] == Key_Hold)
		{
			DashPower = true;
		}
	}
	else if (fClimbJumpMaxTime > fClimbJumpTime && MybeforeState == Player_ClimbJump && !bCeiling)
	{
 		MyState = MyFSM.GetState(MyState, pEvent_ClimbJump);
	}
	else
	{
		bClimb = false;
		bClimbJumpRight = false;
		bClimbJumpleft = false;
		ClimbJumpEffect.Release();
	}
#pragma endregion
	
	if (bDamege)
	{
		MyState = MyFSM.GetState(MyState, pEvent_Damege);
	}

	if (fStartMotionTime < fStartMotionMaxTime)
	{
		MyState = MyFSM.GetState(MyState, pEvent_Start);
		BeforeArrowkey = 'D';
		bGround = true;
	}
	if (bVictory)
	{
		MyState = MyFSM.GetState(MyState, pEvent_Victory);
		BeforeArrowkey = 'D';
	}

	if (MyState != Player_Dash)
	{
		DashEffect.Release();
		SingleSoundManeger.Stop(iDashSound);
	}
	if (bDeatth)
	{
		MyState = MyFSM.GetState(MyState, pEvent_Death);
	}

	std::map<DWORD, SssPlayer*>::iterator SetControlState = MyStateList.find(MyState);
	MyControlState = SetControlState->second;
	if (MyState != MybeforeState)
	{
		MyControlState->SpriteImege->Init();
		MyControlState->fSoundSize = 0;
	}
	
	ClimbEffect.Frame();
	ClimbJumpEffect.Frame();
	DashEffect.Frame();
	DashEffectSprite->Frame();

	if (MyState == Player_Dash)
	{
		MyRect.right = 57;
		MyRect.bottom = 44;
	}
	else
	{
		MyRect.right = 39;
		MyRect.bottom = 58;
	}

	MyCollider->SetRect(MyRect);

	MyControlState->Frame();
	MyPos.x = MyRealPos->x;
	MyPos.y = MyRealPos->y;

	CheckBeforeTime += GetSecPerFrame;
	if(CheckBeforeTime >= CheckBeforeMaxTime)
	{
		MyBeforePos.x = MyRealPos->x;
		MyBeforePos.y = MyRealPos->y;
		CheckBeforeTime -= CheckBeforeMaxTime;
	}


	MyCollider->SetPoint(MyPos);

	AttackerPoint.y = MyPos.y - 80;

	if (bStopLeft || bStopRight)
	{
		if (bStopLeft)
		{
			AttackerPoint.x = MyPos.x + 30;
		}
		else
		{
			AttackerPoint.x = MyPos.x - 30;
		}
	}
	else if(bClimbJumpleft || bClimbJumpRight)
	{
		if (bClimbJumpleft)
		{
			AttackerPoint.x = MyPos.x + 30;
		}
		else
		{
			AttackerPoint.x = MyPos.x - 30;
		}
	}
	else
	{
		if (CheckArrowkey == 'D')
		{
			AttackerPoint.x = MyPos.x + 30;
		}
		else if (CheckArrowkey == 'A')
		{
			AttackerPoint.x = MyPos.x - 30;
		}
		else if (BeforeArrowkey == 'D')
		{
			AttackerPoint.x = MyPos.x + 30;
		}
		else
		{
			AttackerPoint.x = MyPos.x - 30;
		}
	}
	MyAttacker.SetPosition(AttackerPoint);
	if (MyState != Player_Death && MyState != Player_Start && MyState != Player_Victory)
	{
		MyAttacker.Frame();
	}

	BeforeArrowkey = CheckArrowkey != 0 ? CheckArrowkey : BeforeArrowkey;
	MybeforeState = MyState;
	iSoundIndex = -1;

	CheckBlock = false;
	bCheckStop = false;

	return true;
}
bool SssPlayer::Render()
{

	RECT CameraRect;
	CameraRect.left = MyPos.x - 250;
	CameraRect.top = MyPos.y - 250;
	CameraRect.right = MyPos.x + 250;
	CameraRect.bottom = MyPos.y + 250;
	BitBlt(MyScreen, 0, 0, CameraRect.right, CameraRect.bottom,
		MyOffScreen, CameraRect.left, CameraRect.top, SRCCOPY);

	MyControlState->Render();

	if (DemegeDraw)
	{
		static SssImege AlphaDraw;
		AlphaDraw.BlendDrawer(MyOffScreen, MyScreen, CameraRect, 0);
	}
	else
	{
		BitBlt(MyOffScreen, CameraRect.left, CameraRect.top, CameraRect.right, CameraRect.bottom,
			MyScreen, 0, 0, SRCCOPY);
	}
	if (MyState == Player_Dash)
	{
		POINT EffectPoint = MyPos;
		EffectPoint.y += 20;
		if (CheckArrowkey == 'D')
		{
			EffectPoint.x -= 120;
			DashEffectSprite->Draw(MyOffScreen, EffectPoint, 2, IDO_RECT);
		}
		else if (CheckArrowkey == 'A')
		{
			EffectPoint.x += 120;
			DashEffectSprite->Draw(MyOffScreen, EffectPoint, 2, IDO_WidthMirror);
		}
	}
	if (MyState != Player_Death && MyState != Player_Start && MyState != Player_Victory)
	{
		MyAttacker.Render();
	}
	
	if (BeforeArrowkey != CheckArrowkey || MyState != Player_Dash)
	{
		DashEffectSprite->Init();
	}

	ClimbEffect.Render();
	ClimbJumpEffect.Render();
	DashEffect.Render();

	
	bReady = false;

	return true;
}
bool SssPlayer::Release()
{
	std::map<DWORD, SssPlayer*>::iterator Itor = MyStateList.begin();
	while (Itor != MyStateList.end())
	{
		Itor->second->Release();
		delete Itor->second;
		Itor++;
	}
	MyStateList.clear();
	MyAttacker.Release();
	CollisionManeger.DeleteColider(MyCollider);
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	ClimbEffect.Release();
	ClimbJumpEffect.Release();
	DashEffect.Release();
	
	delete MyRealPos;
	return true;
}
bool SssPlayer::CheckEvent(SssObject& TargetObject)
{

	if (TargetObject.GetName() == L"WallObject" || TargetObject.GetName() == L"GroundObject")
	{
		POINT TargetPos = TargetObject.GetPos();
		RECT TargetRect = TargetObject.GetRect();
		CheckBlock = true;
		//float PosScale;
		if (roundf(MyBeforePos.y + (MyRect.bottom / 2)) > roundf(TargetPos.y - (TargetRect.bottom / 2)) &&
			roundf(MyBeforePos.y - (MyRect.bottom / 2)) < roundf(TargetPos.y + (TargetRect.bottom / 2)))
		{
			if ((TargetObject.GetName() == L"WallObject"))
			{
				if (roundf(MyBeforePos.x) <= roundf(TargetPos.x - TargetRect.right / 2))
				{
					if (roundf(MyRealPos->x + (MyRect.right / 2)) >= roundf(TargetPos.x - (TargetRect.right / 2))
						|| (MyRealPos->x >= TargetPos.x - (TargetRect.right / 2)))
					{
						MyRealPos->x = roundf(TargetPos.x - (TargetRect.right / 2) - (MyRect.right / 2));
						if (!bGround)
						{
							bClimb = true;
						}
						bStopRight = true;
						bClimbJumpRight = true;

						bStopLeft = false;
						bClimbJumpleft = false;

						bCheckStop = true;
					}

				}
				else if (roundf(MyBeforePos.x >= (TargetPos.x + TargetRect.right / 2)))
				{
					if (roundf(MyRealPos->x - MyRect.right / 2) <= roundf(TargetPos.x + TargetRect.right / 2)
						|| roundf(MyRealPos->x) <= roundf(TargetPos.x + TargetRect.right / 2))
					{
						MyRealPos->x = roundf((TargetPos.x + TargetRect.right / 2) + (MyRect.right / 2));
						if (!bGround)
						{
							bClimb = true;
						}
						bStopLeft = true;
						bClimbJumpleft = true;

						bStopRight = false;
						bClimbJumpRight = false;

						bCheckStop = true;
					}
				}
			}
		}
		if (TargetObject.GetName() == L"GroundObject")
		{
			if (roundf(MyBeforePos.y) <= roundf(TargetPos.y - (TargetRect.bottom / 2)))
			{
				if (roundf(MyRealPos->y + (MyRect.bottom / 2)) >= roundf(TargetPos.y - (TargetRect.bottom / 2))
					|| roundf(MyRealPos->y) >= roundf(TargetPos.y - (TargetRect.bottom / 2)))
				{
					MyRealPos->y = TargetPos.y - (TargetRect.bottom / 2) - (MyRect.bottom / 2);
					bGround = true;
					bTeleport = false;
				}
			}
			else if (roundf(MyBeforePos.y) >= roundf(TargetPos.y + (TargetRect.bottom / 2)))
			{
				if (MyState != Player_Victory)
				{
					if ((roundf(MyRealPos->y - MyRect.bottom / 2)) <= roundf(TargetPos.y + TargetRect.bottom / 2)
						|| roundf(MyRealPos->y) <= roundf(TargetPos.y + TargetRect.bottom / 2))
					{
						MyRealPos->y = roundf((TargetPos.y + TargetRect.bottom / 2) + (MyRect.bottom / 2));
						MyRealPos->y += 1;
						bCeiling = true;
					}
				}

			}
		}
	}
	if (!GodMode)
	{
		if (!bShield && !bDamege)
		{
			if (TargetObject.GetName() == L"MainBossObject" || TargetObject.GetName() == L"Boss_Bullet" ||
				TargetObject.GetName() == L"SubBossObject")
			{
				bDamege = true;
				MyHP -= 1;
			}
		}
	}
		
	
	return true;
}

SssPlayer::SssPlayer()
{
	
}
SssPlayer::~SssPlayer()
{
}