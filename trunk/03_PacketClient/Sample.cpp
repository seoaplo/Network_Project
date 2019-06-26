#include "SServerStd.h"
#include "Protocol.h"
#include <conio.h>

DWORD WINAPI RecvThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (1)
	{
		char recvbuf[256] = { 0, };
		UPACKET sendpacket;
		ZeroMemory(&sendpacket, sizeof(sendpacket));

		int iRecvByte = recv(sock, (char*)&sendpacket.ph, 4, 0);
		if (iRecvByte == 0)
		{
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("서버 종료 됨");
			break;
		}
		iRecvByte = recv(sock, sendpacket.msg, sendpacket.ph.len-4, 0);

		if (iRecvByte == 0)
		{
			break;
		}
		printf("%s", sendpacket.msg);
	}
	closesocket(sock);
	return 1;
}

DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET sock = (SOCKET) arg;
	char buf[256] = {0, };
	int iEnd = 0;

	while (1)
	{
		fgets(buf, 256, stdin);
		if(buf[0] == '\n') break;
		int iMsgSize = strlen(buf);

		UPACKET sendpacket;
		ZeroMemory(&sendpacket, sizeof(sendpacket));
		sendpacket.ph.len = PACKET_HEADER_SIZE + iMsgSize;
		sendpacket.ph.type = PACKET_CHAR_MSG;
		memcpy(sendpacket.msg, buf, iMsgSize);

		// 윈도우 받기, 보내기 버퍼가 준비되어 있다.
		int iSendByte = send(sock,
							(char*)&sendpacket,
							sendpacket.ph.len, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			E_MSG("send");
			break;
		}
	}
	closesocket(sock);
	return 0;
}

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	unsigned long iMode = 0;
	ioctlsocket(sock, FIONBIO, &iMode);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192.168.0.27");

	int ret = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return;
	}

	DWORD iSendThreadID;
	HANDLE hThreadSend = CreateThread(0, 0, SendThread, (void*)sock, 0, &iSendThreadID);

	DWORD iRecvThreadID;
	HANDLE hThreadRecv = CreateThread(0, 0, RecvThread, (void*)sock, 0, &iRecvThreadID);

	// 대기 함수

	WaitForSingleObject(hThreadSend, INFINITE);
	WaitForSingleObject(hThreadRecv, INFINITE);

	CloseHandle(hThreadSend);
	CloseHandle(hThreadRecv);

	WSACleanup();
}