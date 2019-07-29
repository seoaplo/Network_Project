#include "SssSubBoss2.h"


bool SssSubBoss2::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 500, 500);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	MyPos = TargetPos;
	
	MyRect.left = 196;
	MyRect.top = 8;
	MyRect.right = 87 + MyRect.left;
	MyRect.bottom = 123 + MyRect.top;

	UINT Key = SingleImegeManeger.CreateImege(MyRect, L"../../../data/SubBoss2.bmp", WindowDC);
	MyReadyImege = SingleImegeManeger.GetImege(Key);

	MyRect.left = 406;
	MyRect.top = 4;
	MyRect.right = 76 + MyRect.left;
	MyRect.bottom = 131 + MyRect.top;

	Key = SingleImegeManeger.CreateImege(MyRect, L"../../../data/SubBoss2.bmp", WindowDC);
	MyAttackImege = SingleImegeManeger.GetImege(Key);

	MyRect.left = 314;
	MyRect.top = 157;
	MyRect.right = 36 + MyRect.left;
	MyRect.bottom = 22 + MyRect.top;

	Key = SingleImegeManeger.CreateImege(MyRect, L"../../../data/SubBoss2.bmp", WindowDC);
	MyReadyWeponImege = SingleImegeManeger.GetImege(Key);

	MyRect.left = 442;
	MyRect.top = 149;
	MyRect.right = 102 + MyRect.left;
	MyRect.bottom = 31 + MyRect.top;
	Key = SingleImegeManeger.CreateImege(MyRect, L"../../../data/SubBoss2.bmp", WindowDC);
	MyAttackWeponImege = SingleImegeManeger.GetImege(Key);
	
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 80 * 3;
	MyRect.bottom = 131 * 3;

	iSoundIndex = SingleSoundManeger.Load("../../../data/SubBoss2.wav");
	MyCollider = &CollisionManeger.AddCollider(MyPos, MyRect, this, Col_Rect);

	MyColor = RGB(255, 0, 255);

	bAttackReady = false;
	bAttack = false;

	fAttackReadyTime = 0.0f;
	fAttackReadyMaxTime = 0.4f;

	fAttackTime = 0.0f;
	fAttackMaxTime = 3.0f;

	MySpawnPos = TargetPos;
	ObjectName = L"SubBossObject";

	MyPos.x = -500;
	MyPos.y = -500;
	MyRealPos.x = MyPos.x;
	MyRealPos.y = MyPos.y;
	MyCollider->SetPoint(MyPos);
	return true;
}
bool SssSubBoss2::Frame()
{
	if (bAttackReady && fAttackReadyTime < fAttackReadyMaxTime)
	{
		fAttackReadyTime += GetSecPerFrame;
	}
	else if(bAttackReady)
	{
		bAttackReady = false;
		fAttackReadyTime = 0;
		bAttack = true;
	}

	if (bAttack && fAttackTime < fAttackMaxTime)
	{
 		fAttackTime += GetSecPerFrame;
		MyRealPos.x += 800 * GetSecPerFrame;
	}
	else if (bAttack)
	{
		bAttack = false;
		fAttackTime = 0;
		MyRealPos.x = -500;
		MyRealPos.y = -500;
	}
	MyPos.x = MyRealPos.x;
	MyPos.y = MyRealPos.y;
	MyCollider->SetPoint(MyPos);
	return true;
}
bool SssSubBoss2::Render()
{
	
	if (bAttackReady)
	{
		MyReadyImege->TransDraw(MyOffScreen, MyPos, 3, MyColor, IDO_RECT);
		MyPos.y -= 200;
		MyPos.x += 45;
		MyReadyWeponImege->TransDraw(MyOffScreen, MyPos, 3, MyColor, IDO_RECT);

	}
	else if (bAttack)
	{
		MyAttackImege->TransDraw(MyOffScreen, MyPos, 3, MyColor, IDO_RECT);
		MyPos.x += 75;
		MyPos.y += 150;
		MyAttackWeponImege->TransDraw(MyOffScreen, MyPos, 3, MyColor, IDO_RECT);
	}
	return true;
}
bool SssSubBoss2::Release()
{
	
	CollisionManeger.DeleteColider(MyCollider);
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	return true;
}
bool SssSubBoss2::CheckEvent(SssObject& TargetObject)
{
	return true;
}



SssSubBoss2::SssSubBoss2()
{
}


SssSubBoss2::~SssSubBoss2()
{
}
