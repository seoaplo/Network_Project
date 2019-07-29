#pragma once
#include "Protocol.h"

class SScopeRock_CS
{
	CRITICAL_SECTION& m_cs;
public:
	explicit SScopeRock_CS(CRITICAL_SECTION& Input) : m_cs(Input)
	{
		EnterCriticalSection(&m_cs);
	}
	~SScopeRock_CS()
	{
		LeaveCriticalSection(&m_cs);
	}
};

class SmartMutex
{
	HANDLE m_Handle;
public:
	HANDLE Getter()
	{
		return m_Handle;
	}
public:
	SmartMutex()
	{
		m_Handle = CreateMutex(NULL, FALSE, NULL);
	}
	~SmartMutex()
	{
		CloseHandle(m_Handle);
	}
};

class SScopeRock_Mutex
{
	SmartMutex& m_Mutex;
public:
	explicit SScopeRock_Mutex(SmartMutex& Mutex) : m_Mutex(Mutex)
	{
		WaitForSingleObject(m_Mutex.Getter(), INFINITE);
	}
	~SScopeRock_Mutex()
	{
		ReleaseMutex(m_Mutex.Getter());
	}
};