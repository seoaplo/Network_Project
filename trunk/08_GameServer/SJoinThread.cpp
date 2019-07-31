#include "SJoinThread.h"

DWORD WINAPI JoinThread(LPVOID arg)
{
	while (1)
	{
		if (I_JoinPacketPool.Empty() == true) continue;
		SPacket UserPacket = I_JoinPacketPool.Pop();
		int UserNum = 0;
		SUser& TargetUser = I_UserPool.GetUser(UserPacket.UserID);

		switch (UserPacket.pack.Header.type)
		{
		case PACKET_JOIN_SIGNIN_CS:
		{
			USER_NUM UserNumber;
			UserNumber.iUserNum = UserNum;

			PACKET pack;
			pack.Header.type = PACKET_JOIN_USER_SC;
			pack.Header.len = PACKET_HEADER_SIZE + sizeof(USER_NUM);
			ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);
			memcpy(pack.msg, &UserNumber, sizeof(USER_NUM));

			TargetUser.PushSendPacket(pack);
		}break;
		case PACKET_CHAR_NAME_CS_SEND:
		{
			C_STR UserName = UserPacket.pack.msg;
			TargetUser.SetName(UserName);

			PACKET Packet;
			Packet.Header.type = PACKET_CHAR_NAME_SC_REQ;
			Packet.Header.len = PACKET_HEADER_SIZE + sizeof(USER_NAME_REQ);
			ZeroMemory(Packet.msg, PACKET_MAX_DATA_SIZE);
			USER_NAME_REQ msg;
			msg.bLoginComplete = true;
			memcpy(Packet.msg, &msg, sizeof(USER_NAME_REQ));

			TargetUser.PushSendPacket(Packet);
		}break;
		default:
			E_MSG("알 수 없는 패킷 - JoinPacket");
			break;
		}
	}
	return 1;
}

bool SJoinThread::Init()
{
	m_hThread = CreateThread(0, 0, JoinThread, 0, 0, &m_iThreadID);
	return true;
}
bool SJoinThread::Frame()
{	
	
	return true;
}
bool SJoinThread::Release()
{
	CloseHandle(m_hThread);
	return true;
}


SJoinThread::SJoinThread()
{
}


SJoinThread::~SJoinThread()
{
}
