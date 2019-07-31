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
	#define PACKET_CHAR_NAME_CS_SEND  0x1002 // DATA
	#define PACKET_JOIN_SIGNIN_CS	 0x1003 // x
	#define PACKET_JOIN_USER_SC		 0x1004 // x
	#define PACKET_DRUP_CS_REQ		 0x1005 // x
	#define PACKET_DRUP_SC_ACK		 0x1006 // DATA
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
		bool  bLoginComplete;
	}USER_NAME_REQ;
	typedef struct	{
		int   iIndex;
		char  szName[USER_NAME_SIZE];
	}USER_NAME_ACK;
	typedef struct	{
		char  szName[USER_NAME_SIZE];
		char  msg[PACKET_MAX_DATA_SIZE-20];// 메세지 실제 크기
	}USER_CHAT_MSG;

#define PACKET_USER_LOGIN_CS		0x2000
#define PACKET_USER_LOGIN_SC		0x2001
#define PACKET_USER_LOGOUT			0x2002
#define PACKET_USER_KEYPUSH			0x2003
#define PACKET_USER_KEYUP			0x2004
#define PACKET_USER_STATE_CHANGE	0x2005
#define PACKET_BOSS_STATE_CHANGE	0x2006
#define PACKET_USER_SET				0x2007
#define PACKET_BOSS_SET				0x2008
#define PACKET_WALL_SET				0x2009
#define PACKET_GROUND_SET			0x200A


	typedef struct {
		int   iIndex;
		char  szName[20];
		DWORD UserState;
		POINT UserPoint;
	}USER_OBJECT;

	typedef struct {
		USER_OBJECT UserObj;
		DWORD	KeyNumber;
		bool	KeyState; // false == up, true == push
	}USER_KEY;

	typedef struct {
		USER_OBJECT UserObj;
		bool		login; // false == logout, true == login
	}USER_LOG_STATE;
	
	typedef struct {
		POINT		BossPoint;
		int			TargetIndex;
		DWORD		BossState;
	}BOSS_STATE;

	typedef struct {
		int			iIndex;
		POINT		WallPoint;
	}WALL_STATE;

	typedef struct {
		int			iIndex;
		POINT		GroundPoint;
	}GROUND_STATE;


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
