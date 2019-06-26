#include "SServerStd.h"
#include <conio.h>

DWORD WINAPI RecvThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (1)
	{
		char recvbuf[256] = { 0, };
		int iRecvByte = recv(sock, recvbuf, 256, 0);
		if (iRecvByte == 0)
		{
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("서버 종료\n");
			break;
		}
		printf("%s", recvbuf);
	}
	closesocket(sock);
	return 1;
}

DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char sendbuf[256] = { 0, };
	while (1)
	{
		fgets(sendbuf, 256, stdin);
		if(sendbuf[0] == '\n')
		{
			break;
		}
		int iMsgSize = strlen(sendbuf);

		int iSendByte = send(sock, sendbuf, iMsgSize, 0);
		ZeroMemory(sendbuf, sizeof(sendbuf));
		if (iSendByte == SOCKET_ERROR)
		{
			E_MSG("Send");
			break;
		}
	}
	closesocket(sock);
	return 0;
}

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	unsigned long iMode = 0;
	ioctlsocket(sock, FIONBIO, &iMode);

	SOCKADDR_IN sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(10000);
	sockaddr.sin_addr.s_addr = inet_addr("192.168.0.27");
	int ret = connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr) );
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return;
	}

	DWORD iThreadSendID;
	HANDLE hThreadSend = CreateThread(0, 0, SendThread, (void*)sock, 0, &iThreadSendID);

	DWORD iThreadRecvID;
	HANDLE hThreadRecv = CreateThread(0, 0, RecvThread, (void*)sock, 0, &iThreadRecvID);

	WaitForSingleObject(hThreadSend, INFINITE);
	WaitForSingleObject(hThreadRecv, INFINITE);

	CloseHandle(hThreadSend);
	CloseHandle(hThreadRecv);
	WSACleanup();
}