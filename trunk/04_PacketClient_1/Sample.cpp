#include "SServerStd.h"
#include "Protocol.h"
#include <string>
#include <conio.h>

USER_BASE		g_UserInfo;
USER_CHAT_MSG	g_UserChat;


DWORD WINAPI RecvThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (1)
	{
		char recvbuf[256] = { 0, };
		UPACKET sendpacket;
		ZeroMemory(&sendpacket, sizeof(sendpacket));
		int iRecvByte = 0;
		iRecvByte = recv(sock, (char*)&sendpacket.ph, PACKET_HEADER_SIZE, 0);
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("서버 종료 됨");
			break;
		}
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			memcpy(&packet.ph, (char*)&sendpacket.ph, PACKET_HEADER_SIZE);
			int iNumDataByte = packet.ph.len - PACKET_HEADER_SIZE;
			iRecvByte = 0;
			do {
				int iByte = recv(sock, (char*)&packet.msg[iRecvByte], iNumDataByte - iRecvByte, 0);
				iRecvByte += iByte;
			} while (iNumDataByte > iRecvByte);

			switch (packet.ph.type)
			{
				case PACKET_JOIN_SIGNIN_SC:
				{
					printf("Login Compleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeete!!!!!.\n");
					printf("Chatting Staaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaart!!!!!.\n");

				}break;
				case PACKET_JOIN_USER_SC:
				{
					USER_BASE LoginInfo;
					ZeroMemory(&LoginInfo, sizeof(LoginInfo));

					memcpy(&LoginInfo, packet.msg, sizeof(LoginInfo));

					printf("Login [%s]\n", LoginInfo.szName);
					
				}break;
				case PACKET_CHAR_MSG:
				{
					USER_CHAT_MSG TargetMsg;
					memcpy(&TargetMsg, packet.msg, sizeof(TargetMsg));
					if (strcmp(g_UserChat.szName, TargetMsg.szName) != 0)
					{
						printf("[%s] : %s", TargetMsg.szName, TargetMsg.msg);
					}

				}break;
				case PACKET_DRUP_USERS_SC:
				{
					closesocket(sock);
					return 1;
				}break;
			}
			iRecvByte = 0;
		}
	}
	closesocket(sock);
	return 1;
}

DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET sock = (SOCKET) arg;
	char buf[USER_CHAT_MSG_SIZE] = {0, };

	while (1)
	{
		printf("[%s] : ", g_UserChat.szName);
		fgets(buf, 256, stdin);
		if(strcmp(buf, "/close\n") == 0)
		{
			printf("채팅프로그램을 종료하시겠습니까? ");
			fgets(buf, 256, stdin);
			if (buf[0] ==  'y')
			{
				break;
			}
			else
			{
				continue;
			}
		};
		int iNameSize = strlen(buf);
		
		ZeroMemory(&g_UserChat.msg, sizeof(USER_CHAT_MSG_SIZE));
		memcpy(g_UserChat.msg, buf, USER_CHAT_MSG_SIZE);

		int iMsgSize = sizeof(g_UserChat.msg) + USER_NAME_SIZE;

		UPACKET sendpacket;
		ZeroMemory(&sendpacket, sizeof(sendpacket));
		sendpacket.ph.len = PACKET_HEADER_SIZE + iMsgSize;
		sendpacket.ph.type = PACKET_CHAR_MSG;
		memcpy(sendpacket.msg, &g_UserChat, iMsgSize);

		// 윈도우 받기, 보내기 버퍼가 준비되어 있다.
		int iSendByte = 0;
		do
		{
			int iSendByteOneCycle = send(sock,
				(char*)&sendpacket,
				sendpacket.ph.len - iSendByte, 0);
			if (iSendByte == SOCKET_ERROR)
			{
				E_MSG("send");
				closesocket(sock);
				return 0;
			}
		}
		while(iSendByte >= sendpacket.ph.len);
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
	sa.sin_addr.s_addr = inet_addr("192.168.0.8");

	int ret = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return;
	}
	printf("Server Coneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeect!!!!!.\n");
#pragma region Login
	char buf[256] = { 0, };
	while (1)
	{
		printf("이름을 입력해주세요 : ");
		fgets(buf, 256, stdin);
		if (buf[0] == '\n'
			|| strlen(buf) < 1)
		{
			printf("이름을 다시 입력해주세요.\n");
			continue;
		}
		break;
	}
	int iNameSize = strlen(buf) - 1;

	ZeroMemory(&g_UserInfo, sizeof(g_UserInfo));
	ZeroMemory(&g_UserChat, sizeof(g_UserChat));
	memcpy(g_UserInfo.szName, buf, iNameSize + 1);
	memcpy(g_UserChat.szName, buf, iNameSize);

	int iMsgSize = sizeof(g_UserInfo);

	UPACKET sendpacket;
	ZeroMemory(&sendpacket, sizeof(sendpacket));
	sendpacket.ph.len = PACKET_HEADER_SIZE + iMsgSize;
	sendpacket.ph.type = PACKET_CHAR_NAME_CS_ACK;
	memcpy(sendpacket.msg, &g_UserInfo, iMsgSize);

	// 윈도우 받기, 보내기 버퍼가 준비되어 있다.
	int iSendByte = 0;
	do
	{
		int iSendByteOneCycle = send(sock,
			(char*)&sendpacket,
			sendpacket.ph.len - iSendByte, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			E_MSG("send");
			closesocket(sock);
			return;
		}
	} while (iSendByte >= sendpacket.ph.len);
#pragma endregion

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