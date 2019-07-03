#pragma once
#include "SSelectModel.h"

class SNetWork
{
public:
	std::shared_ptr<SSelectModel> m_pModel;
	
public:
	SNetWork();
	~SNetWork();
};

