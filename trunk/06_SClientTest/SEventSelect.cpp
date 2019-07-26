#include "SEventSelect.h"
#include "SNetWork.h"

bool SEventSelect::Init()
{
	//=========================================================
	// ASYNC-SELECT
	//=========================================================
	m_EventArray[0] = WSACreateEvent();
	int iRet = WSAEventSelect(	m_Sock,
								m_EventHandle, //m_EventArray[0], 
								FD_CONNECT	| FD_CLOSE | FD_READ | FD_WRITE );
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

bool SEventSelect::Frame()
{
	INT iIndex = WSAWaitForMultipleEvents(
											1,
											&m_EventHandle,
											TRUE,
											0,
											FALSE);
	if(iIndex == WSA_WAIT_FAILED) return true;
	if(iIndex == WSA_WAIT_TIMEOUT) return true;
	iIndex -= WSA_WAIT_EVENT_0;

	WSANETWORKEVENTS networkevent;
	// 비신호 상태로 전환한다.
	int iRet = WSAEnumNetworkEvents(
									m_Sock,
									&m_EventHandle,
									&networkevent);

	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	if (networkevent.lNetworkEvents & FD_READ)
	{
		if (networkevent.iErrorCode[FD_READ_BIT] != 0)
		{
			return false;
		}
		if (RecvData() == false)
		{
			return false;
		}
	}
	if (networkevent.lNetworkEvents & FD_WRITE)
	{
		if (networkevent.iErrorCode[FD_CLOSE_BIT] != 0)
		{
			return false;
		}
		SNetWork::m_bConnect = false;
	}

	return true;
}


SEventSelect::SEventSelect(SOCKET sock)
{
	
}


SEventSelect::~SEventSelect()
{
}
