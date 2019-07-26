#pragma once
#include "SSelectModel.h"

class SEventSelect : public SSelectModel
{
public:
	HANDLE				m_EventArray[64];
	HANDLE				m_EventHandle;
	virtual bool		Init();
	virtual bool		Frame();
public:
	SEventSelect(SOCKET sock);
	virtual ~SEventSelect();
};

