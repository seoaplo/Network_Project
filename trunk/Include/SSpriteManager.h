#pragma once
#include "SSprite.h"
#include "STemplate.h"


struct SPRITE_FILE_DATA
{
	T_STR SpriteName;
	int iFrameSize;
	int iLoopFrame;
	std::vector<RECT> RectList;
};

class SSpriteManager : public Singleton<SSpriteManager>
{
private:
	friend Singleton<SSpriteManager>;
	typedef std::map<int, SSprite*>::iterator SpriteItor;		// iterator
private:
	std::map<int, SSprite*> m_SpriteList;
	int m_iMaxSprite;
public:

	int CreateSprite(ID3D11Device* pDevice,  TCHAR* RouteString, TCHAR*  SpriteName);
	bool LoadScript(ID3D11Device* pDevice, TCHAR* RouteString);

	bool ErrorCheck(SPRITE_FILE_DATA& CheckData);


	SSprite* GetSprite(int Key);
	int GetKey(TCHAR* SpriteName);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	SSpriteManager();
private:
	~SSpriteManager();
};

#define I_SpriteManager SSpriteManager::GetInstance()