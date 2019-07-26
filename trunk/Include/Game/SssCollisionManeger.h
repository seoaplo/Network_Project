#pragma once
#include "SssObject.h"
class SssCollisionManeger
{
public:
	std::list<SssCollider*> MyColliders;
	std::vector<SssCollider*> DeleteCol;
public:
	SssCollider& AddCollider(POINT TargetPos, RECT TargetSize, SssObject* TargetObject, int ColliderState);
	bool DeleteColider(SssCollider* TargetCollider);
	bool CheckCrash();
	bool SetDeleteCollision(SssCollider& TargetCol);
	bool DeleteCollision();
	bool Release();
public:
	static SssCollisionManeger& GetInstance()
	{
		static SssCollisionManeger SingleColManeger;
		return SingleColManeger;
	}
public:
	SssCollisionManeger();
	~SssCollisionManeger();
};

#define CollisionManeger SssCollisionManeger::GetInstance()