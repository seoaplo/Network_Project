#include "SServerStd.h"
#include "Protocol.h"
#include <conio.h>

bool g_bChatting = false;
bool g_bExit = false;
USER_BASE		g_UserInfo;
USER_CHAT_MSG	g_UserChat;

bool RecvMsg(SOCKET sock, char* pBuffer, int iNumDataByte)
{
	if(iNumDataByte == 0) return true;
	int iRecvByte = 0;
	do
	{
		int iByte = recv(sock, &pBuffer[iRecvByte], iNumDataByte - iRecvByte, 0);
		if (iByte == 0)
		{
			return false;
		}
		if (iByte == SOCKET_ERROR)
		{
			return false;
		}
		iRecvByte += iByte;
	}while(iNumDataByte > iRecvByte);
	return true;
}

bool SendMsg(SOCKET sock, int type, char* data, int iSize)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.type = type;
	packet.ph.len = PACKET_HEADER_SIZE + iSize;
	if (data != nullptr)
	{
		memcpy(packet.msg, data, iSize);
	}

	int iSendByte = 0;
	do
	{
		int iPacketByte = send(sock, (char*)&packet, packet.ph.len - iSendByte, 0);

		if (iSendByte == SOCKET_ERROR)
		{
			return false;
		}
		iSendByte += iPacketByte;
	}while(packet.ph.len > iSendByte);
	return true;
}

DWORD WINAPI RecvThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (!g_bExit)
	{
		char recvbuf[256] = { 0, };
		UPACKET packet;
		ZeroMemory(&packet, sizeof(packet));

		int iRecvByte = recv(sock, (char*)&packet.ph, PACKET_HEADER_SIZE, 0);
		if (iRecvByte == 0)
		{
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("\n서버 종료");
			break;
		}
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			int iNumDataByte = packet.ph.len - PACKET_HEADER_SIZE;
			if (false == RecvMsg(sock, packet.msg, iNumDataByte))
			{
				break;
			}
			iRecvByte = 0;

			switch (packet.ph.type)
			{
				case PACKET_DRUP_USERS_SC:
				{
					USER_BASE userinfo;
					ZeroMemory(&userinfo, sizeof(USER_BASE));
					memcpy(&userinfo, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
					printf("[%s] Log out", userinfo.szName);
				}break;
				case PACKET_DRUP_SC_ACK:
				{
					g_bExit = true;
					g_bChatting = false;
					printf("\nChatting Eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeend!!!!!");
				}break;
				case PACKET_JOIN_SIGNIN_SC:
				{
					if(g_bChatting) break;
					printf("Login Compleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeete!!!!!\n");
					printf("Chatting Staaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaart!!!!!\n");
					g_bChatting = true;
				}break;
				case PACKET_CHAR_MSG:
				{
					USER_CHAT_MSG message;
					ZeroMemory(&message, sizeof(USER_CHAT_MSG));
					memcpy(&message, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
					printf("\n[%s]%s", message.szName, message.msg);
				}break;
				case PACKET_CHAR_NAME_SC_REQ:
				{
					USER_BASE data;
					ZeroMemory(&data, sizeof(USER_BASE));
					data.iIndex = 8;
					memcpy(data.szName, g_UserInfo.szName, strlen(g_UserInfo.szName));
					SendMsg(sock, PACKET_CHAR_NAME_CS_ACK, (char*)&data, sizeof(USER_BASE));
				}break;
			}
		}
	}
	closesocket(sock);
	return 1;
}

DWORD WINAPI SendThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	char buf[256] = {0,};
	int iEnd = 0;
	while (g_bExit == false)
	{
		if (g_bChatting == false)
		{
			continue;
		}
		printf("%s:", g_UserChat.szName);
		fgets(buf, 256, stdin);
		if (strcmp(buf, "/close\n") == 0)
		{
			printf("채팅프로그램을 종료하시겠습니까? ");
			fgets(buf, 256, stdin);
			if (buf[0] == 'y')
			{
				g_bChatting = false;
				if (false == SendMsg(sock, PACKET_DRUP_CS_REQ, nullptr, 0))
				{
					E_MSG("send");
					break;
				}
				
			}
			continue;
		};
		int iMsgSize = strlen(buf);

		ZeroMemory(&g_UserChat.msg, sizeof(g_UserChat.msg));
		memcpy(&g_UserChat.msg, buf, strlen(buf));
		
		if (false == SendMsg(sock, PACKET_CHAR_MSG, (char*)&g_UserChat, USER_NAME_SIZE + iMsgSize))
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

	DWORD iThreadID;
	HANDLE hThreadSend = CreateThread(0, 0,
		SendThread,
		(void*)sock,
		0,
		&iThreadID);

	DWORD iThreadIDA;
	HANDLE hThreadRecv = CreateThread(0, 0,
		RecvThread,
		(void*)sock,
		0,
		&iThreadIDA);

	// 대기함수	
	WaitForSingleObject(hThreadSend, INFINITE);
	WaitForSingleObject(hThreadRecv, INFINITE);

	CloseHandle(hThreadSend);
	CloseHandle(hThreadRecv);
	WSACleanup();
}