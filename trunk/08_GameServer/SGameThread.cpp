#include "SGameThread.h"

DWORD WINAPI GameThread(LPVOID arg)
{
	while (1)
	{
		if (I_GamePacketPool.Empty() == true) continue;
		SPacket UserPacket = I_GamePacketPool.Pop();
		int UserNum = 0;
		SUser& TargetUser = I_UserPool.GetUser(UserPacket.UserID);
		PACKET pack;

		switch (UserPacket.pack.Header.type)
		{
			case PACKET_USER_LOGIN_CS:
			{

				USER_LOG_STATE UserLogin;
				pack.Header.type = PACKET_USER_LOGIN_SC;
				pack.Header.len = PACKET_HEADER_SIZE + sizeof(USER_LOG_STATE);

				char a = 65;

				for (int iCount = 0; iCount < 10; iCount++)
				{
					ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);
					
					std::string Name;
					Name += a;

					UserLogin.login = true;
					UserLogin.UserObj.iIndex = iCount;
					strcpy_s(UserLogin.UserObj.szName, Name.c_str());
					UserLogin.UserObj.UserPoint.x = 100 + (iCount * 30);
					UserLogin.UserObj.UserPoint.y = 100;
					UserLogin.UserObj.UserState = Player_Air;

					memcpy(pack.msg, &UserLogin, sizeof(USER_LOG_STATE));
					TargetUser.PushSendPacket(pack);

					a++;
				}

				BOSS_STATE BossState;

				pack.Header.type = PACKET_BOSS_SET;
				pack.Header.len = PACKET_HEADER_SIZE + sizeof(BOSS_STATE);
				ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);

				BossState.BossPoint.x = 300;
				BossState.BossPoint.y = 300;
				BossState.BossState = Boss_EventIdle;
				BossState.TargetIndex = 0;

				memcpy(pack.msg, &BossState, sizeof(BOSS_STATE));
				TargetUser.PushSendPacket(pack);

				WALL_STATE WallState;

				pack.Header.type = PACKET_WALL_SET;
				pack.Header.len = PACKET_HEADER_SIZE + sizeof(WALL_STATE);
				ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);

				for (int iCount = 0; iCount < 10; iCount++)
				{
					ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);

					WallState.iIndex = iCount;

					WallState.WallPoint.x = iCount * 300;
					WallState.WallPoint.y = 500;
					memcpy(pack.msg, &WallState, sizeof(WALL_STATE));
					TargetUser.PushSendPacket(pack);
				}

				GROUND_STATE GroundState;

				pack.Header.type = PACKET_GROUND_SET;
				pack.Header.len = PACKET_HEADER_SIZE + sizeof(BOSS_STATE);
				ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);

				for (int iCount = 0; iCount < 10; iCount++)
				{
					ZeroMemory(pack.msg, PACKET_MAX_DATA_SIZE);

					GroundState.iIndex = iCount;

					GroundState.GroundPoint.x = iCount * 100;
					GroundState.GroundPoint.y = 700;

					memcpy(pack.msg, &GroundState, sizeof(GROUND_STATE));
					TargetUser.PushSendPacket(pack);
				}
				printf("\n플레이어 : %d 로그인 완료", UserNum);
			}break;
		}
		
	}
	return 1;
}

bool SGameThread::Init()
{
	m_hThread = CreateThread(0, 0, GameThread, 0, 0, &m_iThreadID);
	return true;
}
bool SGameThread::Frame()
{
	return true;
}
bool SGameThread::Release()
{
	CloseHandle(m_hThread);
	return true;
}

SGameThread::SGameThread()
{
}


SGameThread::~SGameThread()
{
}
