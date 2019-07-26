#include "SNetWork.h"
#include "SAsyncSelect.h"
#include "SEventSelect.h"
#include "SServerStd.h"

std::list<UPACKET>	SNetWork::m_RecvPool;
std::list<UPACKET>	SNetWork::m_SendPool;
bool				SNetWork::m_bConnect = false;

bool SNetWork::SendPacketPool()
{
	if (SNetWork::m_bConnect == false) return true;
	for (UPACKET& packet : SNetWork::m_SendPool)
	{
		if (m_pModel->SendMsg(packet) == false)
		{
			ShutDown();
			break;
		}
	}
	SNetWork::m_SendPool.clear();
	return true;
}

bool SNetWork::SendMsg(int type, char* data, int iSize)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.type = type;
	packet.ph.len = PACKET_HEADER_SIZE + iSize;
	if (data != nullptr)
	{
		memcpy(packet.msg, data, iSize);
	}
	m_SendPool.push_back(packet);
	return true;
}

bool SNetWork::Connect(const char* ip, int port, HWND hWnd)
{
	m_ipAddress = ip;
	m_iPort = port;
	m_hWnd = hWnd;

	if (CreateSock() == false)
	{
		return false;
	}

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(ip);
	int ret = connect(m_Sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return false;
	}
	m_bConnect = true;
	return true;
}

bool SNetWork::CreateSock()
{
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET)
	{
		return false;
	}

	unsigned long iMode = 0;
	ioctlsocket(m_Sock, FIONBIO, &iMode);

	return true;
}

LRESULT	SNetWork::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pModel == nullptr) return 1;
	return m_pModel->MsgProc(hWnd, msg, wParam, lParam);
}

bool	SNetWork::SetModel(std::shared_ptr<SSelectModel> pModel)
{
	if (pModel == nullptr) return false;
	
	m_pModel = pModel;
	m_pModel->m_hWnd = m_hWnd;
	m_pModel->Init();
	return true;
}

bool	SNetWork::ShutDown()
{
	m_bConnect = false;
	closesocket(m_Sock);
	m_RecvPool.clear();
	m_SendPool.clear();
	return true;
}

bool SNetWork::Init()
{
	if (m_pModel == nullptr) return true;
	m_pModel->Init();

	return true;
}
bool SNetWork::Frame()
{
	if (m_pModel == nullptr ) return true;
	if (!m_bConnect)
	{
		// ÀçÁ¢¼Ó
		if (Connect(m_ipAddress.c_str(), m_iPort, m_hWnd) == false)
		{
			ShutDown();
			return false;
		}
		m_pModel->m_Sock = m_Sock;
		m_pModel->Init();
	}

	if (m_pModel->Frame() == false)
	{
		ShutDown();
		return false;
	}

	return true;
}
bool SNetWork::Render()
{
	if (m_pModel == nullptr) return true;
	m_pModel->Render();

	return true;
}
bool SNetWork::Release()
{
	if (m_pModel == nullptr) return true;
	m_pModel->Release();

	return true;
}
SNetWork::SNetWork()
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
	m_pModel = nullptr;
}


SNetWork::~SNetWork()
{
	WSACleanup();
}
