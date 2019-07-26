#include "Sample.h"
char username[] = "서승석";

static Sample* g_Sample;

LRESULT CALLBACK WndProcNew(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	g_Sample->MsgProc(hWnd, iMessage, wParam, lParam);
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

bool Sample::PacketProcess()
{
	for (UPACKET& packet : SNetWork::m_RecvPool)
	{
		switch (packet.ph.type)
		{
			case PACKET_DRUP_USERS_SC:
			{
				USER_BASE userinfo;
				ZeroMemory(&userinfo, sizeof(USER_BASE));
				memcpy(&userinfo, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
				printf("%s: 님이 퇴장하였습니다.", userinfo.szName);
			}break;
			case PACKET_DRUP_SC_ACK:
			{
				printf("\n채팅방 퇴장.");
			}break;
			case PACKET_JOIN_SIGNIN_SC:
			{
				printf("\n채팅방 입장.\n");
			}break;
			case  PACKET_CHAR_MSG:
			{
				USER_CHAT_MSG message;
				ZeroMemory(&message, sizeof(USER_CHAT_MSG));
				memcpy(&message, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);

				C_STR msg = "[";
				msg += message.szName;
				msg += "]";
				msg += message.msg;
				
				int iCnt = SendMessage(m_hList, LB_GETCOUNT, 0, 0);
				if (iCnt > 20)
				{
					SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
				}
				SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)msg.c_str());
			}break;
			case PACKET_CHAR_NAME_SC_REQ :
			{
				USER_BASE data;
				ZeroMemory(&data, sizeof(USER_BASE));
				data.iIndex = 8;
				memcpy(data.szName, username, strlen(username));
				m_Network.m_pModel->SendMsg(m_Network.m_Sock, PACKET_CHAR_NAME_CS_ACK, (char*)&data, sizeof(USER_BASE));
			}break;
		}
	}
	SNetWork::m_RecvPool.clear();
	return true;
}

bool Sample::Init()
{
	// window api control
	T_STR SubWindowName;
	SubWindowName = L"TestSubWindow";

	// 윈도우 클래스 구조체 초기화
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	// 윈도우 클래스 구조체 설정
	wcex.cbSize = sizeof(wcex);
	wcex.hInstance = m_hInstance;
	wcex.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.lpfnWndProc = WndProcNew;
	wcex.lpszClassName = SubWindowName.c_str();
	wcex.lpszMenuName = SubWindowName.c_str();
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 등록
	if (!RegisterClassEx(&wcex))
	{
		return false;
	}


	// 윈도우 생성
	m_hSubWindow = CreateWindowEx(WS_EX_TOPMOST, SubWindowName.c_str(), SubWindowName.c_str(),
								WS_OVERLAPPEDWINDOW,
								0, 0, 1024, 786,
								NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_hSubWindow, SW_SHOW);

	DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE;
	m_hEdit = CreateWindow(L"edit", NULL, style,
		420, 100, 200, 100, m_hSubWindow, (HMENU)100,
		m_hInstance, NULL);

	style = WS_CHILD | WS_VISIBLE;
	m_hButton = CreateWindow(L"button", L"Send", style,
		630, 100, 100, 100, m_hSubWindow, (HMENU)200,
		m_hInstance, NULL);

	style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL;
	m_hList = CreateWindow(L"listbox", NULL, style,
		10, 10, 400, 500, m_hSubWindow, (HMENU)300,
		m_hInstance, NULL);
	SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)L"채팅시작합니다.");
	// 1)초기화
	if (!m_Network.Init())
	{
		return false;
	}
	// 2)접속
	if (!m_Network.Connect("192.168.0.8", 10000, m_hWnd))
	{
		return false;
	}
	// 3)모델 선택
	m_Network.SetModel(make_shared<SStdSelect>(m_Network.m_Sock));
	return true;
}
bool Sample::PreFrame()
{

	return true;
}
bool Sample::Frame()
{
	m_Network.Frame();
	PacketProcess();
	m_Network.SendPacketPool();
	return true;
}
bool Sample::PostFrame()
{
	return true;
}
bool Sample::Release()
{
	m_Network.Release();
	return true;
}
LRESULT Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 200:
		{
			char buffer[MAX_PATH] = { 0, };
			SendMessageA(m_hEdit,
				WM_GETTEXT,
				MAX_PATH,
				(LPARAM)buffer);
			m_Network.SendMsg(PACKET_CHAR_MSG, buffer, sizeof(buffer));
		}
		break;
		}
	}
	}
	return m_Network.MsgProc(hWnd, msg, wParam, lParam);
}

Sample::Sample()
{
	g_Sample = this;
}


Sample::~Sample()
{
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Sample g_Sample;
	RECT rc{ 0, 0, 800, 600 };
	if (!g_Sample.InitWindow(hInstance, nCmdShow, const_cast<TCHAR*>(L"TextureTest2"), rc, false))
	{
		MessageBox(0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ShowCursor(TRUE);
	g_Sample.Run();
	return 1;
}