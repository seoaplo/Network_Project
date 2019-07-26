#pragma once
#include "SssWindow.h"
class SssCore : public SssWindow
{

protected:
	HBITMAP		MyOldBitMap;
	HBITMAP		MyBitMap;
	HDC			MyhMemoryDC;
	HDC			MyOutPutDC;
	bool		bDebug;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Renderer();
	virtual bool Release();
	
public:
	virtual bool BeginInit();
	virtual bool BeginFrame();
	virtual bool BeginRenderer();
	
public:
	virtual bool EndInit();
	virtual bool EndFrame();
	virtual bool EndRenderer();

public:
			bool CoreInit();
			bool CoreFrame();
			bool CoreRenderer();
			bool CoreRelease();
			bool Run();

public:
	
public:
	SssCore();
	virtual ~SssCore();
};



