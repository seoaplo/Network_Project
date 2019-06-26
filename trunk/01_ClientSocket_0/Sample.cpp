#include "SServerStd.h"
#include <conio.h>

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	unsigned long iMode = 0;
	ioctlsocket(sock, FIONBIO, &iMode);

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("192.168.0.8");
	int ret = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return;
	}

	iMode = 1;
	ioctlsocket(sock, FIONBIO, &iMode);

	char buf[256] = {0, };
	int iEnd = 0;
	while (1)
	{
		if (_kbhit() == 1)
		{
			int iValue = _getche();
			if(strlen(buf) == 0 && iValue == '\r')
			{
				break;
			}
			if (iValue == '\r')
			{
				buf[strlen(buf)] = '\n';
				int iMsgSize = strlen(buf);
				// 윈도우 받기, 보내기 버퍼가 준비되어 있다.
				int iSendByte = send(sock, buf, iMsgSize, 0);
				if (iSendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						E_MSG("send");
						break;
					}
				}
				ZeroMemory(buf, sizeof(char) * 256);
				iEnd = 0;
				printf("\n");
			}
			else
			{
				if (iEnd < 255)
				{
					buf[iEnd++] = iValue;
				}
			}

		}
		else
		{
			char recvbuf[256] = {0, };
			int iRecvByte = recv(sock, recvbuf, 256, 0);
			if (iRecvByte == 0)
			{
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					E_MSG("connect");
					break;
				}
			}
			printf("%s", recvbuf);
		}
		
	}
	closesocket(sock);
	WSACleanup();
}