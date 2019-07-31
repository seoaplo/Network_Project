#include "SssStage.h"
#include "Game/SssCore.h"
#include "resource.h"

static SssStage* g_Stage;

LRESULT CALLBACK LoginProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_Stage->MsgProc(hWnd, iMessage, wParam, lParam);
}

LRESULT SssStage::MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
	{
		m_hLogin = hWnd;
		m_hEdit = GetDlgItem(m_hLogin, IDC_EDIT1);
		m_hButton = GetDlgItem(m_hLogin, ID_BUTTON);
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		
		case ID_BUTTON:
		{	 
			char buffer[MAX_PATH] = { 0, };
			SendMessageA(m_hEdit,
				WM_GETTEXT,
				MAX_PATH,
				(LPARAM)buffer);

			int iSize = strlen(buffer);
			if (iSize >= USER_NAME_SIZE)
			{
				MessageBox(SssCore::g_pCore->MyhWindow, L"이름을 20자 이내로 적어 주시오.", L"MSG", 0);
				break;
			}

			PACKET pack;
			pack.Header.type = PACKET_CHAR_NAME_CS_SEND;
			pack.Header.len = PACKET_HEADER_SIZE + sizeof(iSize);

			strcpy_s(pack.msg, buffer);
			I_SendPacketPool.Push(pack);

			PlayerName = buffer;
			EndDialog(m_hLogin, NULL);
		}
		break;
		}
	}
	}
	return 0;
}

bool SssStage::InitPlayerArray()
{
	m_PlayerArray.resize(10);
	POINT Point;

	Point.x = -1000;
	Point.y = -1000;

	int iCount = 0;
	for (SssObject& Object : m_PlayerArray)
	{
		Object.Init(MyScreen, Point, MyWindowDC);
	}

	//MyBos->GetPlayer(*Object);
	return true;
}
bool SssStage::InitBoss()
{
	MyBos = new SssMainBoss;
	POINT Point;

	Point.x = -1000;
	Point.y = -1000;

	MyBos->Init(MyScreen, Point, MyWindowDC);
	MyBos->GetPlayer(m_PlayerArray[0]);
	return true;
}
bool SssStage::InitWallArray()
{
	m_WallArray.resize(10);
	
	POINT Point;

	Point.x = -1000;
	Point.y = -1000;

	int iCount = 0;
	for (SssObject& Object : m_WallArray)
	{
		Object.Init(MyScreen, Point, MyWindowDC);
	}

	return true;
}
bool SssStage::InitGroundArray()
{
	m_GroundArray.resize(10);

	POINT Point;

	Point.x = -1000;
	Point.y = -1000;
	int iCount = 0;

	for (SssObject& Object : m_GroundArray)
	{
		Object.Init(MyScreen, Point, MyWindowDC);
	}
	return true;
}

bool SssStage::Init(HDC WindowDC, HDC OffScreen)
{
	iChangeSceen = -1;
	m_fLoginWait = 0.0f;
	m_bLogin = false;

	g_Stage = this;
	m_iIndex = -1;
	m_Client.Init();
	PACKET JoinPack;
	ZeroMemory(&JoinPack, PACKET_MAX_DATA_SIZE);
	JoinPack.Header.type = PACKET_JOIN_SIGNIN_CS;
	JoinPack.Header.len = PACKET_HEADER_SIZE;

	I_SendPacketPool.Push(JoinPack);
	
	DialogBox(SssCore::g_pCore->MyhInstance, MAKEINTRESOURCE(IDD_INPUTNAME), HWND_DESKTOP, LoginProc);

	MyWindowDC = WindowDC;
	MyOffScreenDC = OffScreen;

	MyScreen = CreateCompatibleDC(WindowDC);
	MyScreenBitMap = CreateCompatibleBitmap(WindowDC, 2048, 768);
	OldBitMap = (HBITMAP)SelectObject(MyScreen, MyScreenBitMap);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 2048;
	rect.bottom = 768;
	UINT Key = SingleImegeManeger.CreateImege(rect, L"../../../data/StageGound.bmp", WindowDC);
	MyBackGroundImege = SingleImegeManeger.GetImege(Key);

	iSoundIndex = SingleSoundManeger.Load("../../../data/sigma.mp3");
	
	MyPoint.x = 1024;
	MyPoint.y = 768 / 2;

	CameraPoint.x = 0;
	CameraPoint.y = 0;

	fReadyTime = 0;
	fReadyMaxTime = 3.0f;

	bVictory = false;
	bLose = false;

	VictoryTime = 0.0f;
	VictoryMaxTime = 5.0f;
	LoseTime = 0.0f;
	LoseMaxTime = 5.0f;

	InitGroundArray();
	InitWallArray();
	InitPlayerArray();
	InitBoss();

	SingleSoundManeger.Play(iSoundIndex, FMOD_LOOP_NORMAL);
	SingleSoundManeger.Volume(iSoundIndex, 0.5, false);
	return true;
}

bool SssStage::Frame()
{
	PacketProcess();
	m_Client.Frame();
	if (!m_bLogin)
	{
		m_fLoginWait += GetSecPerFrame;
		if (m_fLoginWait >= 10.0f)
		{
			iChangeSceen = SC_TITLE;
			MessageBox(SssCore::g_pCore->MyhWindow, L"접속시간이 초과 되었습니다.", L"MSG", 0);
		}
		return true;
	}

	SingleInput.CheckKeyState(VK_SPACE);
	SingleInput.CheckKeyState(VK_SHIFT);
	SingleInput.CheckKeyState(VK_CONTROL);
	SingleInput.CheckKeyState(VK_ESCAPE);

	if (SingleInput.GetMyStateKey(VK_ESCAPE) == Key_Push)
	{
		bLose = true;
	}
	for (SssWall& WallObject : m_WallArray)
	{
		WallObject.Frame();
	}
	for (SssGround& GroundObject : m_GroundArray)
	{
		GroundObject.Frame();
	}
	MyBos->Frame();
	if (fReadyTime < fReadyMaxTime)
	{
		MyBos->SetReady();
	}
	if (bLose)
	{
		MyBos->SetLose();
	}
	if (MyBos->GetDeath())
	{
		bVictory = true;
	}
	for (SssPlayer& Player : m_PlayerArray)
	{
		Player.Frame();
		if (Player.m_iIndex == m_iIndex)
		{
			if (Player.GetPos().x >= 516 && Player.GetPos().x <= 1536)
			{
				CameraPoint.x = Player.GetPos().x - 516;
			}
			else if (Player.GetPos().x < 516)
			{
				CameraPoint.x = 0;
			}
			else if (Player.GetPos().x < 1536)
			{
				CameraPoint.x = 1024;
			}
			/*if (fReadyTime < fReadyMaxTime)
			{
				Player.SetReady();
			}
			if (bVictory)
			{
				Player->SetVictory();
			}
			if (Player->GetDeath())
			{
				bLose = true;
			}*/
			Player.SetKeyState(VK_SPACE, SingleInput.GetMyStateKey(VK_SPACE));
			Player.SetKeyState(VK_SHIFT, SingleInput.GetMyStateKey(VK_SHIFT));
			Player.SetKeyState(VK_CONTROL, SingleInput.GetMyStateKey(VK_CONTROL));
			
			Player.SetKeyState('A', SingleInput.GetMyStateKey('A'));
			Player.SetKeyState('D', SingleInput.GetMyStateKey('D'));
		}
	}
	
	if (fReadyTime < fReadyMaxTime)
	{
		fReadyTime += GetSecPerFrame;
	}
	if (bVictory && VictoryTime < VictoryMaxTime)
	{
		VictoryTime += GetSecPerFrame;
		SingleSoundManeger.Volume(iSoundIndex, GetSecPerFrame / VictoryMaxTime, false);
	}
	else if (VictoryTime >= VictoryMaxTime)
	{
		iChangeSceen = SC_ResultWin;
	}
	if (bLose && LoseTime < LoseMaxTime)
	{
		LoseTime += GetSecPerFrame;
		SingleSoundManeger.Volume(iSoundIndex, GetSecPerFrame / LoseMaxTime, false);
	}
	else if(LoseTime >= LoseMaxTime)
	{
		iChangeSceen = SC_ResultLose;
	}
	
	return true;
}
bool SssStage::Render()
{

	COLORREF bkColor = RGB(255, 0, 0);
	HBRUSH hbrBack = CreateSolidBrush(bkColor);
	HBRUSH hbrOld = (HBRUSH)SelectObject(MyScreen, hbrBack);

	PatBlt(MyScreen, 0, 0, 2048, 768, PATCOPY);

	DeleteObject(SelectObject(MyScreen, hbrOld));

	MyBackGroundImege->Draw(MyScreen, MyPoint, 1, SRCCOPY);
	for (SssWall& WallObject : m_WallArray)
	{
		WallObject.Render();
	}
	for (SssGround& GroundObject : m_GroundArray)
	{
		GroundObject.Render();
	}
	MyBos->Render();
	
	for (SssPlayer& Player : m_PlayerArray)
	{
		Player.Render();
	}

	BitBlt(MyOffScreenDC, 0, 0, 1024, 768, MyScreen, CameraPoint.x, CameraPoint.y, SRCCOPY);
	return true;
}
bool SssStage::Release()
{
	m_Client.Release();
	m_bLogin = false;
	return true;

	for (SssWall& WallObject : m_WallArray)
	{
		WallObject.Release();
	}
	for (SssGround& GroundObject : m_GroundArray)
	{
		GroundObject.Release();
	}
	MyBos->Release();

	for (SssPlayer& Player : m_PlayerArray)
	{
		Player.Release();
	}
	m_WallArray.clear();
	m_GroundArray.clear();
	m_PlayerArray.clear();
	MyBos = nullptr;

	SingleSoundManeger.Stop(iSoundIndex);
	DeleteObject(SelectObject(MyScreen, OldBitMap));
	DeleteDC(MyScreen);
	
	m_Client.Release();
	g_Stage = nullptr;
	m_fLoginWait = 0.0f;
	PlayerName.clear();

	return true;
}

bool SssStage::PacketProcess()
{
	if (I_RecvPacketPool.Empty() == false)
	{
		PACKET pack = I_RecvPacketPool.Pop();

		switch (pack.Header.type)
		{
		case PACKET_JOIN_USER_SC:
		{
			m_iIndex = *((int*)pack.msg);
		}break;
		case PACKET_CHAR_NAME_SC_REQ:
		{
			bool LoginComplet;
			LoginComplet = *((bool*)pack.msg);
			if (LoginComplet)
			{
				m_bLogin = true;

				PACKET pack;
				ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);
				pack.Header.type = PACKET_USER_LOGIN_CS;
				pack.Header.len = PACKET_HEADER_SIZE;

				I_SendPacketPool.Push(pack);
			}
			else
			{
				iChangeSceen = SC_TITLE;
				MessageBox(SssCore::g_pCore->MyhWindow, L"접속할 수 없습니다.", L"MSG", 0);
				return false;
			}
		}break;
			
		case PACKET_USER_LOGIN_SC:
		{
			int iIndex = *((int*)pack.msg);
			m_PlayerArray[iIndex].PacketProcess(pack);
		}break;
		case PACKET_BOSS_SET:
		{	BOSS_STATE BossState;
			memcpy(&BossState, pack.msg, sizeof(BOSS_STATE));
			MyBos->GetPlayer(m_PlayerArray[BossState.TargetIndex]);
			MyBos->PacketProcess(pack);
		}break;
		case PACKET_WALL_SET:
		{
			int iIndex = *((int*)pack.msg);
			m_WallArray[iIndex].PacketProcess(pack);
		}break;
		case PACKET_GROUND_SET:
		{			
			int iIndex = *((int*)pack.msg);
			m_GroundArray[iIndex].PacketProcess(pack);
		}break;
		default:
			break;
		}
	}
	return true;
}

SssStage::SssStage()
{
	m_bLogin = false;
}


SssStage::~SssStage()
{
}
