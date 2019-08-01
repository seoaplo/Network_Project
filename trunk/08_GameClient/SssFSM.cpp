#include "SssFSM.h"


void SssFSM::CreateFSM(DWORD iState, DWORD iEvent, DWORD iChangeState)
{
	std::multimap<DWORD, DWORD> NewDWORD;
	NewDWORD.insert(std::make_pair(iEvent, iChangeState));
	StateList.insert(std::make_pair(iState, NewDWORD));
}
DWORD SssFSM::GetState(DWORD iState, DWORD iEvent)
{
	std::multimap<DWORD, std::multimap<DWORD, DWORD>>::iterator CheckStateItor = StateList.begin();
	while (CheckStateItor != StateList.end())
	{
		if (CheckStateItor->first == iState)
		{
			std::multimap<DWORD, DWORD>::iterator CheckEventItor = CheckStateItor->second.begin();
			while (CheckEventItor != CheckStateItor->second.end())
			{
				if (CheckEventItor->first == iEvent)
				{
					return CheckEventItor->second;
				}
				CheckEventItor++;
			}
		}
		CheckStateItor++;
	}
	return -1;
}
SssFSM::SssFSM()
{
}


SssFSM::~SssFSM()
{
	std::multimap<DWORD, std::multimap<DWORD, DWORD>>::iterator ReleaseIter = StateList.begin();
	while (ReleaseIter != StateList.end())
	{
		ReleaseIter->second.clear();
		ReleaseIter++;
	}
	StateList.clear();
}
