#pragma once
#include <Windows.h>
#define PACKET_HEADER_SIZE 4
#define PACKET_MAX_DATA_SIZE 2048

#pragma pack(push, 1)

typedef struct
{
	WORD len;
	WORD type;
}PACKET_HEADER;
typedef struct
{
	PACKET_HEADER	ph;
	char			msg[PACKET_MAX_DATA_SIZE];
}UPACKET;

// UNPACKET
// len = PACKET_HEADER_SIZE + 패킷 크기
// type = 패킷 타입
// msg  = 패킷 내용
#define PACKET_CHAR_MSG 1000
#define PACKET_CHAR_NAME_REQ 1001
#define PACKET_CHAR_NAME_ACK 1002
#define PACKET_CHARACTER_INFO 3000

typedef struct
{
	byte	szName;
	int		iIndex;
	int		iData;
}CHARACTER_INFO;

#pragma pack(pop)