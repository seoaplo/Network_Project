#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <process.h>
#include "SUtils.h"

#pragma comment(lib, "ws2_32.lib")

#define PACK_RECV 1000
#define PACK_SEND 2000
#define PACK_END  3000
#define MAX_STREAM_SIZE 4096*5

void E_MSG(const char* pMsg)
{
	void* lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf , 0 , NULL);
		LocalFree(lpMsgBuf);
	return;
}