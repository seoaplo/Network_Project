#include "SssSubBoss1.h"



bool SssSubBoss1::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 500, 500);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	MyPos = TargetPos;
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 206;
	MyRect.bottom = 338;

	ShootPos = MyPos;
	ShootPos.x += 100;
	ShootPos.y -= 120;

	MyColor = RGB(255, 0, 255);
	MyColor2 = RGB(29, 112, 189);

	bAttackReady = false;
	fAttackReadyTime = 0.0f;
	fAttackReadyMaxTime = 0.5f;

	bAttack = false;
	fAttackTime = 0.0f;
	fAttackMaxTime = 5.0f;

	bAttackEnd = false;
	fAttackEndTime = 0.0f;
	fAttackEndMaxTime = 0.5f;

	UINT ImegeKey = SingleSpriteManeger.CreateSprite
	(L"../Data/SubBoss1.txt", L"../Data/SubBoss1.bmp", L"SubBoss1Attack", MyColor, WindowDC, fAttackReadyMaxTime);
	SpriteImege = SingleSpriteManeger.GetSprite(ImegeKey);
	
	SpriteImege->Init();

	ImegeKey = SingleSpriteManeger.CreateSprite
	(L"../Data/SubBoss1.txt", L"../Data/SubBoss1.bmp", L"SubBoss1End", MyColor, WindowDC, fAttackEndMaxTime);
	SpriteMask = SingleSpriteManeger.GetSprite(ImegeKey);

	SpriteMask->Init();

	MyDegree = 0.0f;

	ObjectName = L"MainBossObject";

	float Xpos = MyRect.right / 2;
	float Ypos = MyRect.bottom / 2;
	MyLength = sqrt((Xpos * Xpos) + (Ypos * Ypos));

	MyCollider = NULL;
	iSoundIndex = SingleSoundManeger.Load("../Data/SubBossBullet.wav");
	SingleSoundManeger.Volume(iSoundIndex, 1, true);

	fBulletShootTime = 0.0f;
	fBulletShootMaxTime = 0.3f;
	fBulletSpeed = 1000;
	return true;
}
bool SssSubBoss1::Frame()
{
	std::list<SssSubBoss1Bullet*>::iterator DeleteItor;
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


	if (bAttackReady && fAttackReadyMaxTime > fAttackReadyTime)
	{
		fAttackReadyTime += GetSecPerFrame;
		SpriteImege->Frame();	
	}
	else if(bAttackReady)
	{
		SpriteImege->Frame();
		bAttackReady = false;
		bAttack = true;
		fAttackReadyTime = 0;
	}
	if (bAttack && fAttackTime < fAttackMaxTime)
	{
		SpriteImege->Frame();
		fAttackTime += GetSecPerFrame;
		float Xpos = PlayerPoint.x - ShootPos.x;
		float Ypos = ShootPos.y - PlayerPoint.y;

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
			SingleSoundManeger.PlayEffect(iSoundIndex);
			SssPoint Distance;
			Distance.x = PlayerPoint.x - ShootPos.x;
			Distance.y = PlayerPoint.y - ShootPos.y;

			float fScala = sqrt(Distance.x* Distance.x + Distance.y * Distance.y);
			Distance.x /= fScala;
			Distance.y /= fScala;

			SssPoint BulletPoint;
			BulletPoint.x = ShootPos.x;
			BulletPoint.y = ShootPos.y;

			SssSubBoss1Bullet* NewBullet = new SssSubBoss1Bullet;
			NewBullet->Init(MyOffScreen, MyPos, MyWindowDC, fBulletSpeed, Distance, BulletPoint, MyDegree - 90);
			BulletList.push_back(NewBullet);
		}
	}
	else if (bAttack)
	{
		SpriteImege->Frame();
		bAttack = false;
		bAttackEnd = true;
		SpriteMask->Init();
		fAttackTime = 0;
	}
	if (bAttackEnd && fAttackEndMaxTime > fAttackEndTime)
	{
		SpriteMask->Frame();
		fAttackEndTime += GetSecPerFrame;
	}
	else if (bAttackEnd)
	{
		SpriteMask->Frame();
		bAttackEnd = false;
		SpriteImege->Init();
		fAttackEndTime = 0;
	}
	
	

	
	std::list<SssSubBoss1Bullet*>::iterator Itor;
	for (Itor = BulletList.begin(); Itor != BulletList.end(); Itor++)
	{
		(*Itor)->Frame();
	}
	
	return true;
}
bool SssSubBoss1::Render()
{
	std::list<SssSubBoss1Bullet*>::iterator Itor;
	for (Itor = BulletList.begin(); Itor != BulletList.end(); Itor++)
	{
		(*Itor)->Render();
	}
	if (!bAttackEnd)
	{
		SpriteImege->Draw(MyOffScreen, MyPos, 2, IDO_RECT);
	}
	else
	{
		SpriteMask->Draw(MyOffScreen, MyPos, 2, IDO_RECT);
	}
	
	return true;
}
bool SssSubBoss1::Release()
{
	std::list<SssSubBoss1Bullet*>::iterator Itor;
	for (Itor = BulletList.begin(); Itor != BulletList.end(); Itor++)
	{
		(*Itor)->Release();
		delete *Itor;
	}
	BulletList.clear();

	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	return true;
}
bool SssSubBoss1::CheckEvent(SssObject& TargetObject)
{
	return true;
}

SssSubBoss1::SssSubBoss1()
{

}


SssSubBoss1::~SssSubBoss1()
{
}
