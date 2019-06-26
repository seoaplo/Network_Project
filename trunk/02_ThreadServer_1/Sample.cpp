#include "SServerStd.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;
CRITICAL_SECTION cs;

struct SUser
{
	static SOCKET	findSock;
	SOCKET			sock;
	SOCKADDR_IN		clientaddr;
	char			recvbuf[256];
	bool			operator()(SUser& val) const
	{
		return (findSock == val.sock);
	}
};

class SScopeRock_CS
{
	CRITICAL_SECTION& m_cs;
public:
	explicit SScopeRock_CS(CRITICAL_SECTION& Input) : m_cs(Input)
	{
		EnterCriticalSection(&m_cs);
	}
	~SScopeRock_CS()
	{
		LeaveCriticalSection(&m_cs);
	}
};

std::list<SUser*> g_UserList;

template<typename T> class SCheck
{
public:
	bool operator() (T val) const
	{
		return (val->sock == m_iSock);
	}
	SOCKET m_iSock;
};

void AddUser(	SOCKET	sock,
				SOCKADDR_IN clientaddr	)
{
	SUser*	client = new SUser;
	client->sock = sock;
	client->clientaddr = clientaddr;
	{
		SScopeRock_CS scope(cs);
		g_UserList.push_back(client);
	}

	printf("\n立加 ip = [%s] port = [%d]=%d",
		inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port),
		g_UserList.size());
}

void AddUser(SUser* user)
{
	{
		SScopeRock_CS scope(cs);
		g_UserList.push_back(user);
	}
	printf("\n立加 ip = [%s] port = [%d]=%d",
		inet_ntoa(user->clientaddr.sin_addr),
		ntohs(user->clientaddr.sin_port),
		g_UserList.size());
}

void DelUser(SOCKET sock)
{
	SScopeRock_CS scope(cs);

	SCheck<SUser*> check;
	check.m_iSock = sock;
	std::list<SUser*>::iterator iter;
	iter = find_if(g_UserList.begin(),
					g_UserList.end(),
					check);
	SUser* pUser = (SUser*)*iter;
	closesocket(pUser->sock);

	printf("\n辆丰 ip = [%s] port = [%d]=%d",
		inet_ntoa(pUser->clientaddr.sin_addr),
		ntohs(pUser->clientaddr.sin_port),
		g_UserList.size());
	delete *iter;
	g_UserList.erase(iter);
}

void Broadcast(const char* msg, int ibyte)
{
	SScopeRock_CS scope(cs);

	for (SUser* user : g_UserList)
	{
		//Sleep(1);
		int iSendByte = send(user->sock, msg, ibyte, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			closesocket(user->sock);
		}
	}
}

DWORD WINAPI UserThread(LPVOID arg)
{
	SUser* user = (SUser*)arg;
	while (1)
	{
		int iRecvByte = recv(user->sock, user->recvbuf, 256, 0);
		if (iRecvByte == 0)
		{
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			break;
		}
		Broadcast(user->recvbuf, iRecvByte);
	}
	DelUser(user->sock);
	return 1;
}

void main()
{
	InitializeCriticalSection(&cs);

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(listensock, (SOCKADDR*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("bind");
		return;
	}

	ret = listen(listensock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		E_MSG("listen");
		return;
	}
	printf("Sever Staaaaaaaaaaaaaaaaaaaaaaaaaart!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	int addlen = sizeof(SOCKADDR_IN);
	while (1)
	{
		SUser* user = new SUser;
		user->sock = accept(listensock, (SOCKADDR*)&user->clientaddr, &addlen);
		if (user->sock == INVALID_SOCKET)
		{
			E_MSG("accept");
		}
		AddUser(user);

		DWORD iThreadID;
		HANDLE hThreadSend = CreateThread(0, 0, UserThread, (void*)user, 0, &iThreadID);

	}
	closesocket(listensock);
	WSACleanup();

	DeleteCriticalSection(&cs);
}