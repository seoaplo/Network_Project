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
		return false;
	}
	ret = listen(m_listensock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		E_MSG("Server::listen");
		return false;
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
	return true;
}

bool SPacketThread::PacketProcess()
{
	FD_ZERO(&m_rSet);
	FD_ZERO(&m_wSet);
	FD_SET(m_listensock, &m_rSet);
	for (SUser& User : I_UserPool.GetUserPool())
	{
		if (User.GetConnect())
		{
			FD_SET(User.GetSocket(), &m_rSet);
			FD_SET(User.GetSocket(), &m_wSet);
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
		SOCKET			UserSock = NULL;
		SOCKADDR_IN		UserAddr;
		UserSock = accept(m_listensock, (SOCKADDR*)&UserAddr,
			&m_addlen);
		if (UserSock == INVALID_SOCKET)
		{
			E_MSG("Server::accept");
		}
		int UserNum;
		UserNum = I_UserPool.PushUser(UserSock);
		SUser& TargetUser = I_UserPool.GetUser(UserNum);
		USER_NUM UserNumber;
		UserNumber.iUserNum = UserNum;

		PACKET pack;
		pack.Header.type = PACKET_JOIN_USER_SC;
		pack.Header.len = PACKET_HEADER_SIZE + sizeof(USER_NUM);
		ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);
		memcpy(pack.msg, &UserNumber, sizeof(USER_NUM));

		TargetUser.PushSendPacket(pack);

		TargetUser.SetConnect();
		TargetUser.SetSockAddr(UserAddr);
		printf("\nConnect ip : %s, Number : %d", inet_ntoa(UserAddr.sin_addr), UserNumber);
	}
	for (SUser& User : I_UserPool.GetUserPool())
	{
		if (User.GetConnect() == false) continue;

		if (FD_ISSET(User.GetSocket(), &m_rSet))
		{
			if (User.Recv() == false)
			{
				User.SetConnect(false);
				User.SetDisConnect();
			}
		}
		if (FD_ISSET(User.GetSocket(), &m_wSet))
		{
			if (User.Send() == false)
			{
				User.SetConnect(false);
				User.SetDisConnect();
			}
		}
	}

	// 유저삭제
	int	iMax = 0;
	int DeleteArray[USER_MAXSIZE];
	ZeroMemory(DeleteArray, sizeof(int) * USER_MAXSIZE);

	for (SUser& User : I_UserPool.GetUserPool())
	{
		if (User.GetDisConnect() == true)
		{
			printf("\n종료 ip : %s, port : %d, num : %d",
				inet_ntoa(User.GetSockAddr().sin_addr),
				ntohs(User.GetSockAddr().sin_port),
				User.GetNumber());

			DeleteArray[iMax] = User.GetNumber();
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
