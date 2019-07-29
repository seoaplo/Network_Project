#include "SssTitleObject.h"

bool SssTitleObject::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const char* SoundStirng, RECT TargetRect,
	const TCHAR* RouteString, const TCHAR* RectString, const TCHAR* RectRouteString, COLORREF TargetColor, bool Check, float fScale)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;
	if (SoundStirng != NULL)
	{
		iSoundIndex = SingleSoundManeger.Load(SoundStirng);
	}
	UINT Key = SingleSpriteManeger.CreateSprite(RectRouteString, RouteString, RectString, TargetColor, WindowDC, 1);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);
	bTrans = true;
	bCheckMouse = Check;
	MyfScale = fScale;
	MyRect = TargetRect;
	MyRect.left = MyPos.x - (MyRect.right / 2);
	MyRect.top = MyPos.y - (MyRect.bottom / 2);
	MyRect.right += MyRect.left;
	MyRect.bottom += MyRect.top;
	bInside = false;
	return true;
}
bool SssTitleObject::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const char* SoundStirng, RECT TargetRect,
	const TCHAR* RouteString, const TCHAR* RectString, const TCHAR* RectRouteString, const TCHAR* MaskRouteString, bool Check, float fScale)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;
	if (SoundStirng != NULL)
	{
		iSoundIndex = SingleSoundManeger.Load(SoundStirng);
	}
	else
	{
		iSoundIndex = -1;
	}
	UINT Key = SingleSpriteManeger.CreateSprite(RectRouteString, RouteString, RectString, MaskRouteString, WindowDC, 1);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);
	bTrans = false;
	bCheckMouse = Check;
	MyfScale = fScale;
	MyRect = TargetRect;
	MyRect.left = MyPos.x - (MyRect.right / 2);
	MyRect.top = MyPos.y - (MyRect.bottom / 2);
	MyRect.right += MyPos.x;
	MyRect.bottom += MyPos.y;
	bInside = false;
	return true;
}
bool SssTitleObject::Frame()
{
	SpriteImege->Frame();
	if (!bTrans)
	{
		SpriteMask->Frame();
	}
	POINT MyMousePoint = GetMousePoint;
	if (bCheckMouse)
	{
		if (MyRect.left <= MyMousePoint.x && MyRect.right >= MyMousePoint.x &&
			MyRect.top <= MyMousePoint.y && MyRect.bottom >= MyMousePoint.y)
		{
			if (SingleInput.GetKeyState.dwMouseL == Key_Push)
			{
				if (iSoundIndex >= 0)
				{
					SingleSoundManeger.PlayEffect(iSoundIndex);
				}
			}
		}
	}
	
	return true;
}
bool SssTitleObject::Render()
{
	if (MyfScale > 0)
	{
		SpriteImege->Draw(MyOffScreen, MyPos, MyfScale, IDO_RECT);
	}
	else
	{
		SpriteImege->Draw(MyOffScreen, MyPos, -MyfScale, IDO_RECT);
	}
	if (!bTrans)
	{
		if (MyfScale > 0)
		{
			SpriteMask->Draw(MyOffScreen, MyPos, MyfScale, IDO_RECT);
		}
		else
		{
			SpriteMask->Draw(MyOffScreen, MyPos, -MyfScale, IDO_RECT);
		}
	}
	return true;
}
bool SssTitleObject::Release()
{
	return true;
}

SssTitleObject::SssTitleObject()
{
}


SssTitleObject::~SssTitleObject()
{
}


bool SssStartObject::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const char* SoundStirng, RECT TargetRect,
	const TCHAR* RouteString, const TCHAR* RectString, const TCHAR* RectRouteString, COLORREF TargetColor, bool Check, float fScale)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;
	if (SoundStirng != NULL)
	{
		iSoundIndex = SingleSoundManeger.Load(SoundStirng);
	}
	UINT Key = SingleSpriteManeger.CreateSprite(RectRouteString, RouteString, RectString, TargetColor, WindowDC, 1);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);
	bTrans = true;
	bCheckMouse = Check;
	MyfScale = fScale;
	MyRect = TargetRect;
	MyRect.left = MyPos.x - (MyRect.right / 2);
	MyRect.top = MyPos.y - (MyRect.bottom / 2);
	MyRect.right += MyRect.left;
	MyRect.bottom += MyRect.top;
	bInside = false;
	return true;
}
bool SssStartObject::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const char* SoundStirng, RECT TargetRect,
	const TCHAR* RouteString, const TCHAR* RectString, const TCHAR* RectRouteString, const TCHAR* MaskRouteString, bool Check, float fScale)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;
	if (SoundStirng != NULL)
	{
		iSoundIndex = SingleSoundManeger.Load(SoundStirng);
	}
	else
	{
		iSoundIndex = -1;
	}
	UINT Key = SingleSpriteManeger.CreateSprite(RectRouteString, RouteString, RectString, MaskRouteString, WindowDC, 1);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);
	bTrans = false;
	bCheckMouse = Check;
	MyfScale = fScale;
	MyRect = TargetRect;
	MyRect.left = MyPos.x - (MyRect.right / 2);
	MyRect.top = MyPos.y - (MyRect.bottom / 2);
	MyRect.right += MyPos.x;
	MyRect.bottom += MyPos.y;
	bInside = false;
	return true;
}
bool SssStartObject::Frame()
{
	SpriteImege->Frame();
	if (!bTrans)
	{
		SpriteMask->Frame();
	}
	POINT MyMousePoint = GetMousePoint;
	if (bCheckMouse)
	{
		if (MyRect.left <= MyMousePoint.x && MyRect.right >= MyMousePoint.x &&
			MyRect.top <= MyMousePoint.y && MyRect.bottom >= MyMousePoint.y)
		{
			if (SingleInput.GetKeyState.dwMouseL == Key_Push)
			{
				if (iSoundIndex >= 0)
				{
					SingleSoundManeger.PlayEffect(iSoundIndex);
					bChangeSceen = true;
				}
			}
		}
	}

	return true;
}
bool SssStartObject::Render()
{
	if (MyfScale > 0)
	{
		SpriteImege->Draw(MyOffScreen, MyPos, MyfScale, IDO_RECT);
	}
	else
	{
		SpriteImege->Draw(MyOffScreen, MyPos, -MyfScale, IDO_RECT);
	}
	if (!bTrans)
	{
		if (MyfScale > 0)
		{
			SpriteMask->Draw(MyOffScreen, MyPos, MyfScale, IDO_RECT);
		}
		else
		{
			SpriteMask->Draw(MyOffScreen, MyPos, -MyfScale, IDO_RECT);
		}
	}
	return true;
}
bool SssStartObject::Release()
{
	return true;
}


bool SssExitObject::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const char* SoundStirng, RECT TargetRect,
	const TCHAR* RouteString, const TCHAR* RectString, const TCHAR* RectRouteString, COLORREF TargetColor, bool Check, float fScale)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;
	if (SoundStirng != NULL)
	{
		iSoundIndex = SingleSoundManeger.Load(SoundStirng);
	}
	UINT Key = SingleSpriteManeger.CreateSprite(RectRouteString, RouteString, RectString, TargetColor, WindowDC, 1);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);
	bTrans = true;
	bCheckMouse = Check;
	MyfScale = fScale;
	MyRect = TargetRect;
	MyRect.left = MyPos.x - (MyRect.right / 2);
	MyRect.top = MyPos.y - (MyRect.bottom / 2);
	MyRect.right += MyRect.left;
	MyRect.bottom += MyRect.top;
	bInside = false;
	return true;
}
bool SssExitObject::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const char* SoundStirng, RECT TargetRect,
	const TCHAR* RouteString, const TCHAR* RectString, const TCHAR* RectRouteString, const TCHAR* MaskRouteString, bool Check, float fScale)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;
	if (SoundStirng != NULL)
	{
		iSoundIndex = SingleSoundManeger.Load(SoundStirng);
	}
	else
	{
		iSoundIndex = -1;
	}
	UINT Key = SingleSpriteManeger.CreateSprite(RectRouteString, RouteString, RectString, MaskRouteString, WindowDC, 1);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);
	bTrans = false;
	bCheckMouse = Check;
	MyfScale = fScale;
	MyRect = TargetRect;
	MyRect.left = MyPos.x - (MyRect.right / 2);
	MyRect.top = MyPos.y - (MyRect.bottom / 2);
	MyRect.right += MyPos.x;
	MyRect.bottom += MyPos.y;
	bInside = false;
	return true;
}
bool SssExitObject::Frame()
{
	SpriteImege->Frame();
	if (!bTrans)
	{
		SpriteMask->Frame();
	}
	POINT MyMousePoint = GetMousePoint;
	if (bCheckMouse)
	{
		if (MyRect.left <= MyMousePoint.x && MyRect.right >= MyMousePoint.x &&
			MyRect.top <= MyMousePoint.y && MyRect.bottom >= MyMousePoint.y)
		{
			if (SingleInput.GetKeyState.dwMouseL == Key_Push)
			{
				if (iSoundIndex >= 0)
				{
					SingleSoundManeger.PlayEffect(iSoundIndex);
					return false;
				}
			}
		}
	}

	return true;
}
bool SssExitObject::Render()
{
	if (MyfScale > 0)
	{
		SpriteImege->Draw(MyOffScreen, MyPos, MyfScale, IDO_RECT);
	}
	else
	{
		SpriteImege->Draw(MyOffScreen, MyPos, -MyfScale, IDO_RECT);
	}
	if (!bTrans)
	{
		if (MyfScale > 0)
		{
			SpriteMask->Draw(MyOffScreen, MyPos, MyfScale, IDO_RECT);
		}
		else
		{
			SpriteMask->Draw(MyOffScreen, MyPos, -MyfScale, IDO_RECT);
		}
	}
	return true;
}
bool SssExitObject::Release()
{
	return true;
}

