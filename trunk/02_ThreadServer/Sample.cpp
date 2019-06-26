#include "SServerStd.h"

DWORD WINAPI UserThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (1)
	{
		char recvbuf[256] = {0, };
		int iRecvByte = recv(sock, recvbuf, 256, 0);
		if (iRecvByte == 0)
		{
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			E_MSG("유저 종료");
			break;
		}
		printf("\n%s", recvbuf);
		int iSendByte = send(sock, recvbuf, 256, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			E_MSG("유저 종료");
			break;
		}

	}
	closesocket(sock);
	return 1;
}

void main()
{
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
	while(1)
	{
		SOCKADDR_IN clientaddr;
		SOCKET clientsock;
		int clientaddrSize = sizeof(SOCKADDR_IN);
		clientsock = accept(listensock, (SOCKADDR*)&clientaddr, &clientaddrSize);
		if (clientsock == INVALID_SOCKET)
		{
			E_MSG("accept");
		}
		DWORD iThreadID;
		HANDLE hThreadSend = CreateThread(0, 0, UserThread, (void*)clientsock, 0, &iThreadID);

	}
	closesocket(listensock);
	WSACleanup();
}