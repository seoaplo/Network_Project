#include "SPacketThread.h"

DWORD WINAPI PacketThread(LPVOID arg)
{
	SPacketThread* Process = (SPacketThread*)arg;

	bool ProcessSuccess = true;
	while (ProcessSuccess)
	{
		ProcessSuccess = Process->PacketProcess();
	}
	return 1;
}

bool SPacketThread::Init()
{
	
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET)
	{
		return false;
	}
	unsigned long iMode = 0;
	ioctlsocket(m_Sock, FIONBIO, &iMode);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192.168.0.27");
	int ret = connect(m_Sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("Client::Connect");
		return false;
	}

	printf("\nConnect Complete\n");
	//-------------------SELECT---------------------------
	m_addlen = sizeof(SOCKADDR_IN);


	m_hThread = CreateThread(0, 0, PacketThread, (LPVOID)this, 0, &m_iThreadID);
	return true;
}
bool SPacketThread::Frame()
{
	return true;
}
bool SPacketThread::Release()
{
	CloseHandle(PacketThread);
	closesocket(m_Sock);
	return true;
}

bool SPacketThread::PacketProcess()
{
	FD_ZERO(&m_rSet);
	FD_ZERO(&m_wSet);
	FD_SET(m_Sock, &m_rSet);
	FD_SET(m_Sock, &m_wSet);

	timeval time;
	time.tv_sec = 0; // 초
	time.tv_usec = 17;// 마이크로 초

	int iRet = select(0, &m_rSet, &m_wSet, NULL, &time);
	if (iRet == SOCKET_ERROR)
	{
		return true;
	}
	if (iRet == 0) return true;// timeout

	if (FD_ISSET(m_Sock, &m_rSet))
	{
		if (Recv() == false)
		{
			E_MSG("Client::Recv");
			return false;
		}
	}
	if (FD_ISSET(m_Sock, &m_wSet))
	{
		if (Send() == false)
		{
			E_MSG("Client::Send");
			return false;
		}
	}
	return true;
}
void SPacketThread::Put(char* pBuffer, DWORD dwByte)
{
	//m_dwWritePos 다음 버퍼 위치
	//m_dwStartPos 패킷의 시작 위치
	//m_dwReadPos  받은 데이터 크기
	if (m_dwWritePos + dwByte >= MAX_STREAM_SIZE)
	{
		if (m_dwReadPos > 0)
		{
			memmove(m_szPackStream, &m_szPackStream[m_dwStartPos], m_dwReadPos);
		}
		m_dwStartPos = 0;
		m_dwWritePos = m_dwReadPos;
	}
	memcpy(&m_szPackStream[m_dwWritePos], pBuffer, dwByte);
	m_dwWritePos += dwByte;
	m_dwReadPos += dwByte;

	if (m_dwReadPos >= PACKET_HEADER_SIZE)
	{
		PACKET CheckPacket;
		memcpy(&CheckPacket.Header, &m_szPackStream[m_dwStartPos], PACKET_HEADER_SIZE);
		// 받은 데이터 크기(1개의 패킷보다 크면)
		if (CheckPacket.Header.len <= m_dwReadPos)
		{
			do {

				PACKET UserPacket;
				ZeroMemory(&UserPacket, sizeof(UserPacket));
				memcpy(&UserPacket, &m_szPackStream[m_dwStartPos], CheckPacket.Header.len);

				m_dwReadPos -= UserPacket.Header.len;
				m_dwStartPos += UserPacket.Header.len;

				// packet push
				I_RecvPacketPool.Push(UserPacket);

				if (m_dwReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				memcpy(&CheckPacket.Header, &m_szPackStream[m_dwStartPos], PACKET_HEADER_SIZE);
				if (CheckPacket.Header.type == 0)
				{
					break;
				}
			} while (CheckPacket.Header.len <= m_dwReadPos);
		}
	}
}
bool SPacketThread::Recv()
{
	SScopeRock_Mutex Lock(m_Mutex);
	DWORD dwTransfer = 0, flag = 0;
	int iRet = recv(m_Sock, m_szRecvBuffer, MAX_USER_BUFFER_SIZE, NULL);
	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			E_MSG("Server::recv");
			return false;
		}
	}
	else if (iRet == 0)
	{
		return false;
	}
	else
	{
		Put(m_szRecvBuffer, iRet);
	}
	return true;
}

bool SPacketThread::Send()
{
	SScopeRock_Mutex Lock(m_Mutex);
	while (I_SendPacketPool.Empty() == false)
	{
		PACKET pack;
		ZeroMemory(&pack, MAX_USER_BUFFER_SIZE);
		memcpy(&pack, &I_SendPacketPool.Pop(), MAX_USER_BUFFER_SIZE);

		int iSendByte = 0;
		do {
			int iPacketByte = send(m_Sock,
				(char*)&pack, pack.Header.len - iSendByte, 0);
			if (iSendByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() !=
					WSAEWOULDBLOCK)
				{
					E_MSG("Server::send");
					return false;
				}
			}
			else
			{
				iSendByte += iPacketByte;
			}
		} while (pack.Header.len > iSendByte);
	}
}

SPacketThread::SPacketThread()
{
}


SPacketThread::~SPacketThread()
{
}
