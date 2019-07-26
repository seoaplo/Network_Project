#include "SssAttacker.h"



bool SssAttacker::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 1024, 768);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	MyPos = TargetPos;
	MyWindowDC = WindowDC;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 96;
	rect.bottom = 64;
	UINT ImegeKey = SingleImegeManeger.CreateImege(rect, L"../Data/Attacker3.bmp", WindowDC);
	MyImege = SingleImegeManeger.GetImege(ImegeKey);
	MyColor = RGB(255, 0, 255);
	MyCollider = &CollisionManeger.AddCollider(MyPos, rect, this, Col_Rect);
	MyDegree = 0.0f;
	ObjectName = L"AttackerObject";

	float Xpos = rect.right / 2;
	float Ypos = rect.bottom / 2;
	MyLength = sqrt((Xpos * Xpos) + (Ypos * Ypos));

	iSoundIndex = SingleSoundManeger.Load("../Data/Shoot.wav");

	fBulletShootTime = 0.0f;
	fBulletShootMaxTime = 0.15f;
	fBulletSpeed = 1000;

	return true;
}
bool SssAttacker::Frame()
{
	std::list<SssPlayerBullet*>::iterator DeleteItor;
	DeleteBulletList.reserve(BulletList.size());
	for (DeleteItor = BulletList.begin(); DeleteItor != BulletList.end(); DeleteItor++)
	{
		if ((*DeleteItor)->DeleteThis())
		{
			(*DeleteItor)->Release();
			delete (*DeleteItor);
			DeleteBulletList.push_back(*DeleteItor);
		}
	}
	for (int iCount = 0; iCount < DeleteBulletList.size(); iCount++)
	{
		BulletList.remove(DeleteBulletList[iCount]);
	}
	DeleteBulletList.clear();

	MyCollider->SetPoint(MyPos);
	POINT MousePoint = GetMousePoint;


	if (MyPos.x > 512 && MyPos.x < 1536)
	{
		MousePoint.x += MyPos.x - 512;
	}
	else if (MyPos.x > 1536)
	{
		MousePoint.x += 1024;
	}


	float Xpos = MousePoint.x - MyPos.x;
	float Ypos = MyPos.y - MousePoint.y;

	float fDistance = sqrt((Xpos * Xpos) + (Ypos * Ypos));
	float Radian = acos(Xpos / fDistance);
	MyDegree = Radian * 180 / 3.141592;

	if (Ypos < 0)
	{
		MyDegree = -MyDegree;
	}

	fBulletShootTime += GetSecPerFrame;
	if (fBulletShootTime >= fBulletShootMaxTime)
	{
		fBulletShootTime -= fBulletShootMaxTime;
		if (SingleInput.GetKeyState.dwMouseL == Key_Push ||
			SingleInput.GetKeyState.dwMouseL == Key_Hold)
		{
			SingleSoundManeger.PlayEffect(iSoundIndex);
			SingleSoundManeger.Volume(iSoundIndex, 0.2, false);
			SssPoint Distance;
			Distance.x = MousePoint.x - MyPos.x;
			Distance.y = MousePoint.y - MyPos.y;

			float fScala = sqrt(Distance.x* Distance.x + Distance.y * Distance.y);
			Distance.x /= fScala;
			Distance.y /= fScala;

			SssPoint BulletPoint = Distance;
			BulletPoint.x *= MyLength * 0.8;
			BulletPoint.y *= MyLength * 0.8;
			BulletPoint.x += MyPos.x;
			BulletPoint.y += MyPos.y;

			SssPlayerBullet* NewBullet = new SssPlayerBullet;
			NewBullet->Init(MyOffScreen, MyPos, MyWindowDC, fBulletSpeed, Distance, BulletPoint, MyDegree);
			BulletList.push_back(NewBullet);
		}
	}
	std::list<SssPlayerBullet*>::iterator Itor;
	for (Itor = BulletList.begin(); Itor != BulletList.end(); Itor++)
	{
		(*Itor)->Frame();
	}
	return true;
}
bool SssAttacker::Render()
{
	std::list<SssPlayerBullet*>::iterator Itor;
	for (Itor = BulletList.begin(); Itor != BulletList.end(); Itor++)
	{
		(*Itor)->Render();
	}
	MyImege->TransRotateDraw(MyOffScreen, MyPos, MyDegree, MyColor, -0.5, 0.5);
	return true;
}
bool SssAttacker::Release()
{
	std::list<SssPlayerBullet*>::iterator Itor;
	for (Itor = BulletList.begin(); Itor != BulletList.end(); Itor++)
	{
		(*Itor)->Release();
		delete *Itor;
	}
	BulletList.clear();

	CollisionManeger.DeleteColider(MyCollider);
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	return true;
}
bool SssAttacker::CheckEvent(SssObject& TargetObject)
{
	return true;
}
bool SssAttacker::SetPosition(POINT TargetPoint)
{
	MyPos = TargetPoint;
	return true;
}


SssAttacker::SssAttacker()
{
}


SssAttacker::~SssAttacker()
{
}
