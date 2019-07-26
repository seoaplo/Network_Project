#include "SUser.h"

bool SUser::Init()
{
	m_bReady = false;
	bConnect = false;

	m_iNum = -1;

	m_dwEndPos		= 0;
	m_dwStartPos	= 0;
	m_dwReadPos		= 0;
	m_dwWritePos	= 0;

	ZeroMemory(m_szRecvBuffer, sizeof(char) * MAX_USER_BUFFER_SIZE);
	ZeroMemory(m_szPackStream, sizeof(char) * MAX_STREAM_SIZE);
}

bool SUser::Release()
{
	m_bReady = false;
	bConnect = false;

	m_iNum = -1;

	m_dwEndPos = 0;
	m_dwStartPos = 0;
	m_dwReadPos = 0;
	m_dwWritePos = 0;

	ZeroMemory(m_szRecvBuffer, sizeof(char) * MAX_USER_BUFFER_SIZE);
	ZeroMemory(m_szPackStream, sizeof(char) * MAX_STREAM_SIZE);

	closesocket(m_sock);
}

void SUser::Put(char* pBuffer, DWORD dwByte)
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
				
				SPacket UserPacket;
				ZeroMemory(&UserPacket, sizeof(UserPacket));
				memcpy(&UserPacket, &m_szPackStream[m_dwStartPos], UserPacket.pack.Header.len);

				m_dwReadPos -= UserPacket.pack.Header.len;
				m_dwStartPos += UserPacket.pack.Header.len;

				// packet push
				I_PacketPool.Push(UserPacket);

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
bool SUser::Recv()
{
	SScopeRock_Mutex Lock(m_Mutex);
	DWORD dwTransfer, flag = 0;
	int iRet = recv(m_sock, m_szRecvBuffer, MAX_USER_BUFFER_SIZE, NULL);
	if (iRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			E_MSG("Server::recv");
			return false;
		}
	}
	else
	{
		Put(m_szRecvBuffer, dwTransfer);
	}
	return true;
}
bool SUser::PushSendPacket(PACKET pack)
{
	SScopeRock_Mutex Lock(m_Mutex);
	m_SendPacketPool.push(pack);
	return true;
}
bool SUser::Send()
{
	SScopeRock_Mutex Lock(m_Mutex);
	while (m_SendPacketPool.empty() == false)
	{
		PACKET pack;
		ZeroMemory(&pack, MAX_USER_BUFFER_SIZE);
		memcpy(&pack, &m_SendPacketPool.front(), MAX_USER_BUFFER_SIZE);
		m_SendPacketPool.pop();

		int iSendByte = 0;
		do {
			int iPacketByte = send(m_sock,
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
	return true;
}

SUser::SUser()
{
}


SUser::~SUser()
{
}
