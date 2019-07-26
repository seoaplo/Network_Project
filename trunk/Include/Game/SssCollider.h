#pragma once
#include "SssStd.h"
class SssObject;

enum ColliderState
{
	Col_Point = 0,
	Col_Rect,
	Col_Circle
};
class SssCollider
{
public:
	POINT MyPos;
	RECT MyRect;
	float Myflength;
	SssObject* MyObject;
	int MyiState;
public:
	bool Create(POINT, RECT, SssObject*, int);
	void SetPoint(POINT point)
	{
		MyRect.left += point.x - MyPos.x;
		MyRect.right += point.x - MyPos.x;

		MyRect.top += point.y - MyPos.y;
		MyRect.bottom += point.y - MyPos.y;

		MyPos = point;
	}
	void SetRect(RECT TargetRect)
	{

		MyRect.left = MyPos.x - (TargetRect.right / 2);
		MyRect.right = MyPos.x + (TargetRect.right / 2);

		MyRect.top =  MyPos.y - (TargetRect.bottom / 2);
		MyRect.bottom = MyPos.y + (TargetRect.bottom / 2);
	}
	SssObject* GetSssObject()
	{
		return MyObject;
	}
	bool ColliderCheck(SssCollider& TargetCollider);
private:
	float FindRlength(float x, float y, float x2, float y2);
	bool RectinPoint(SssCollider& TargetCollider);
	bool RectinRect(SssCollider& TargetCollider);
	bool RectinCircle(SssCollider& TargetCollider);
	bool CircleinPoint(SssCollider& TargetCollider);
	bool CircleinRect(SssCollider& TargetCollider);
	bool CircleinCircle(SssCollider& TargetCollider);
public:
	SssCollider();
	~SssCollider();
};

