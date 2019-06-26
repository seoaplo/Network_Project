#include "SServerStd.h"

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
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

	SOCKADDR_IN clientaddr;
	int addlen = sizeof(SOCKADDR_IN);
	SOCKET clientsock;
	printf("\n 서버 시작\n");
	clientsock = accept(listensock,
						(SOCKADDR*)&clientaddr,
						&addlen);
	if (clientsock == INVALID_SOCKET)
	{
		E_MSG("accept");
	}

	printf("접속 address = [%s], port = [%d]\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
	while (1)
	{
		char recvbuf[256] = {0, };
		int iRecvByte = recv(clientsock, recvbuf, 256, 0);
		if(iRecvByte == 0)
		{
			printf("접속 종료 address = [%s], port = [%d]",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("접속 종료 address = [%s], port = [%d]",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			break;
		}
		printf("%s", recvbuf);

		int iSendByte = send(clientsock, recvbuf, strlen(recvbuf), 0);
		if (iSendByte == SOCKET_ERROR)
		{
			E_MSG("send");
			break;
		}
	}
	closesocket(clientsock);
	closesocket(listensock);
	WSACleanup();
}