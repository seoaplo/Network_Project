#pragma once
#include "SUtils.h"
#include "STemplate.h"
#include "STimer.h"
#include "fmod/fmod.hpp"

class SSound
{
private:
	friend class SSoundManager;
private:
	//===============================================================================================
	// SSoundManager Value
	//===============================================================================================
	FMOD::System*			m_pSystem;					// SSoundManager�� ���� System �ּ�
	int						m_iIndex;					// SSoundManager �ȿ��� �ش�Ǵ� ��ȣ
private:
	//===============================================================================================
	// Sound Value
	//===============================================================================================
	FMOD::Sound*			m_pSound;					// ����
	float					m_fVolume;					// ���� ũ��
	FMOD::Channel*			m_pChannel;					// ���� ä��
	std::string				m_csFileName;				// ���� �̸�
public:
	void		Play();
	void		Stop();
	void		Paused();
	void		Volume(int iVolume = 10, bool bUp = true);
	void		PlayEffect();
	void		SetMode(DWORD dwMode);

private:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

private:
	SSound();
	virtual ~SSound();
};