#pragma once
#include "SssStd.h"

const int MySoundMax = MAX_PATH;
class SssSound
{
public:
	
	FMOD::System* MySoundSystem;
	FMOD::Sound* MySoundList[MySoundMax];
	FMOD::Channel* MyChannel[MySoundMax];
	std::map<std::string, int> SoundList;
	int MySoundSize;
public:
	int			Load(char* RouteString);
	void		Play(int iIndex, int SetMode);
	void		PlayEffect(int iIndex);
	void		Stop(int iIndex);
	void		Paused(int iIndex);
	void		Volume(int iIndex, float fVolume, bool bUp = true);
	int			GetSoundSize(int iIndex);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	static SssSound& GetSoundSystem()
	{
		static SssSound SingleSound;
		return SingleSound;
	}
private:
	SssSound() {};
	~SssSound() {};
};

#define SingleSoundManeger SssSound::GetSoundSystem()
//MMX3_BGM_00000.wav