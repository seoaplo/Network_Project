#pragma once
#include "STemplate.h"
#include "SImage.h"

class SImageManager : public Singleton<SImageManager>
{
private:
	friend Singleton<SImageManager>;
	typedef std::map<int, SImage*>::iterator ImageItor;		// iterator
private:
	std::map<int, SImage*> m_ImageList;
	int m_iMaxImage;

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			Load(ID3D11Device* pDevice, const T_STR pShaderPath, const T_STR pFilePath);
	SImage*		GetPtr(int iKey);
	bool		Delete(int iKey);
	
private:
	SImageManager();
public:
	~SImageManager();
};

#define I_ImageManager SImageManager::GetInstance()