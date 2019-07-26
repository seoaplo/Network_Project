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
	m_listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(m_listensock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("Server::bind");
		return;
	}
	ret = listen(m_listensock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		E_MSG("Server::listen");
		return;
	}
	unsigned long iMode = 1;
	ioctlsocket(m_listensock, FIONBIO, &iMode);

	printf("\n서버 시작!!!\n");
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
	closesocket(m_listensock);
}

bool SPacketThread::PacketProcess()
{
	FD_ZERO(&m_rSet);
	FD_ZERO(&m_wSet);
	FD_SET(m_listensock, &m_rSet);
	for (SUser& User : I_UserPool.GetUserPool())
	{
		if (User.bConnect)
		{
			FD_SET(User.m_sock, &m_rSet);
			FD_SET(User.m_sock, &m_wSet);
		}
	}

	timeval time;
	time.tv_sec = 0; // 초
	time.tv_usec = 17;// 마이크로 초

	int iRet = select(0, &m_rSet, &m_wSet, NULL, &time);
	if (iRet == SOCKET_ERROR)
	{
		return true;
	}
	if (iRet == 0) return true;// timeout

	if (FD_ISSET(m_listensock, &m_rSet))
	{
		SOCKET			UserSock;
		SOCKADDR_IN		UserAddr;
		UserSock = accept(UserSock, (SOCKADDR*)&UserAddr,
			&m_addlen);
		if (UserSock == INVALID_SOCKET)
		{
			E_MSG("Server::accept");
		}
		I_UserPool.PushUser(UserSock);
	}
	for (SUser& User : I_UserPool.GetUserPool())
	{
		if (FD_ISSET(User.m_sock, &m_rSet))
		{
			if (User .Recv() == false)
			{
				User.bConnect = false;
			}
		}
		if (FD_ISSET(User.m_sock, &m_wSet))
		{
			User.Send();
		}
	}

	// 유저삭제
	int	iMax = 0;
	int DeleteArray[USER_MAXSIZE];
	ZeroMemory(DeleteArray, sizeof(int) * USER_MAXSIZE);

	for (SUser& User : I_UserPool.GetUserPool())
	{
		if (User.bConnect == false)
		{
			closesocket(User.m_sock);
			printf("\n종료[%s][%d]=%d",
				inet_ntoa(User.m_addr.sin_addr),
				ntohs(User.m_addr.sin_port),
				I_UserPool.GetUserPool().size());
				DeleteArray[iMax] = User.m_iNum;
				iMax++;
		}
	}

	for (int iCount = 0; iCount < iMax; iCount++)
	{
		I_UserPool.DeleteUser(DeleteArray[iCount]);
	}

	while (I_PacketPool.Empty() == false)
	{
		SPacket UserPacket;
		UserPacket = I_PacketPool.Pop();

		if (UserPacket.pack.Header.type & 0x1000)
		{
			I_JoinPacketPool.Push(UserPacket);
		}
		else if (UserPacket.pack.Header.type & 0x2000)
		{
			I_GamePacketPool.Push(UserPacket);
		}
		else
		{
			E_MSG("알 수 없는 패킷 - PacketPool");
		}
	}
	return true;
}

SPacketThread::SPacketThread()
{
}


SPacketThread::~SPacketThread()
{
}
