#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "Client/fmod/fmod.hpp"

#ifdef _WIN64
#pragma comment(lib, "fmod64_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif // _WIN64

#pragma comment (lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "00_SssLibrary.lib")

class SssPoint
{
public:
	float x;
	float y;

	const SssPoint& operator+=(const int& TargetInt)
	{
		this->x += TargetInt;
		this->y += TargetInt;
		return *this;
	}
	const SssPoint& operator+=(const float& Targetfloat)
	{
		this->x += Targetfloat;
		this->y += Targetfloat;
		return *this;
	}
	const SssPoint& operator+=(const POINT& TargetPoint)
	{
		this->x += TargetPoint.x;
		this->y += TargetPoint.y;
		return *this;
	}
	const SssPoint& operator+=(const UINT& TargetInt)
	{
		this->x += TargetInt;
		this->y += TargetInt;
		return *this;
	}
	const SssPoint& operator-=(const int& TargetInt)
	{
		this->x -= TargetInt;
		this->y -= TargetInt;
		return *this;
	}
	const SssPoint& operator-=(const float& Targetfloat)
	{
		this->x -= Targetfloat;
		this->y -= Targetfloat;
		return *this;
	}
	const SssPoint& operator-=(const POINT& TargetPoint)
	{
		this->x -= TargetPoint.x;
		this->y -= TargetPoint.y;
		return *this;
	}
	const SssPoint& operator-=(const UINT& TargetInt)
	{
		this->x -= TargetInt;
		this->y -= TargetInt;
		return *this;
	}
};