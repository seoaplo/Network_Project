#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	// sock == UNSIGN INT POINTER
	// socket(AF, Type, Protocol)
	// SOCK_STREAM�� �ڵ����� TCP_IP�� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ���� �̸�
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));

	sa.sin_family = AF_INET;	// ���ͳ�
	sa.sin_port = htons(10000); // host to network short
	sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.8");

	// connect( ����, �̸�, 
	while (1)
	{
		printf("EXIT = enter\n");
		connect(sock, (SOCKADDR*)&sa, sizeof(sa));
		char Sendbuffer[256] = { 0, };
		fgets(Sendbuffer, 256, stdin);

		if (Sendbuffer[0] == '\n')
		{
			break;
		}
		int iMsgSize = strlen(Sendbuffer);
		int iSendByte = send(sock, Sendbuffer, strlen(Sendbuffer), 0);

		if (iSendByte == SOCKET_ERROR)
		{
			printf("���� ����");
			break;
		}

		char Recvbuffer[256] = { 0, };
		int RecvByte = recv(sock, Recvbuffer, 256, 0);
		if (RecvByte == 0)
		{
			printf("endgame");
			ZeroMemory(Sendbuffer, sizeof(Sendbuffer));
		}
		else if (RecvByte == SOCKET_ERROR)
		{
			printf("���� ����");
			break;
		}

		Recvbuffer[RecvByte] = '\n';
		printf("%s", Recvbuffer);
	}
	closesocket(sock);
	WSACleanup();
}