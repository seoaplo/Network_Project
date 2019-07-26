#include "SStdSelect.h"
#include "SNetWork.h"
bool SStdSelect::Init()
{
	return true;
}

bool SStdSelect::Frame()
{
	FD_ZERO(&rSet);
	FD_ZERO(&wSet);

	FD_SET(m_Sock, &rSet);
	FD_SET(m_Sock, &wSet);

	timeval time;
	time.tv_sec = 10;	// second
	time.tv_usec = 0;	// micro second

	int iRet = select(0, &rSet, &wSet, NULL, &time);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}

	if (iRet == 0) return true;  // timeout

	if (FD_ISSET(m_Sock, &rSet))
	{
		if (RecvData() == false)
		{
			SNetWork::m_bConnect = false;
		}
	}

	if (FD_ISSET(m_Sock, &wSet))
	{
		// printf(".");
	}
	return true;
}


SStdSelect::SStdSelect(SOCKET sock)
{
	m_Sock = sock;
}


SStdSelect::~SStdSelect()
{
}
