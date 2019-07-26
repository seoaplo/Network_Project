#pragma once
#include "SSelectModel.h"

class SStdSelect : public SSelectModel
{
public:
	FD_SET rSet;
	FD_SET wSet;

public:
	virtual bool	Init();
	virtual bool	Frame();
public:
	SStdSelect(SOCKET sock);
	~SStdSelect();
};

