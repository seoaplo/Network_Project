#pragma once
#include <windows.h>
#define PACKET_HEADER_SIZE 4
#define PACKET_MAX_DATA_SIZE 2048
#define MAX_USER_BUFFER_SIZE PACKET_MAX_DATA_SIZE+ PACKET_HEADER_SIZE

#pragma pack( push, 1)
	typedef struct
	{
		WORD len;   // 데이터 길이+헤더길이
		WORD type;  // 패킷 타입
	}PACKET_HEADER;
	typedef struct {
		PACKET_HEADER Header;
		char          msg[PACKET_MAX_DATA_SIZE];
	}PACKET;

	#define PACKET_CHAR_MSG			 0x1000 // DATA
	#define PACKET_CHAR_NAME_SC_REQ  0x1001 // DATA
	#define PACKET_CHAR_NAME_CS_ACK  0x1002 // DATA
	#define PACKET_JOIN_SIGNIN_CS	 0x1003 // x
	#define PACKET_JOIN_USER_SC		 0x1004 // x
	#define PACKET_DRUP_CS_REQ		 0x1005 // x
	#define PACKET_DRUP_SC_ACK		 0x1006 // x
	#define PACKET_DRUP_USERS_SC	 0x1007 // DATA

	typedef struct 
	{
		int iUserNum;
	}USER_NUM;
	typedef struct {
		int   iIndex;
		char  szName[20];		
	}USER_BASE;
	#define USER_BASE_SIZE 24
	#define USER_NAME_SIZE 20
	typedef struct	{
		USER_BASE base;
		char  msg[30];
	}USER_NAME_REQ;
	typedef struct	{
		int   iIndex;
		char  szName[USER_NAME_SIZE];
	}USER_NAME_ACK;
	typedef struct	{
		char  szName[USER_NAME_SIZE];
		char  msg[PACKET_MAX_DATA_SIZE-20];// 메세지 실제 크기
	}USER_CHAT_MSG;

#pragma pack(pop)

struct SPacket
{
	int		UserID;
	PACKET	pack;
	SPacket& operator=(const SPacket& Packet)
	{
		SPacket RetPack;
		RetPack.UserID = Packet.UserID;

		ZeroMemory(&RetPack.pack, MAX_USER_BUFFER_SIZE);
		memcpy(&RetPack.pack, &Packet.pack, MAX_USER_BUFFER_SIZE);

		return RetPack;
	}
};
