#pragma once
#include "SUtils.h"
#include "SDirectWrite.h"
#include "STemplate.h"


class STimer 
{
private:
	//===================================================================================
	// Basis Time
	//===================================================================================
	LARGE_INTEGER	m_Frequency;		// �ʴ� ���ļ�
	LARGE_INTEGER	m_Current;			// ���� �ð�
	LARGE_INTEGER	m_Frame;			// ���� ������ �ð� üũ
	float			m_fSecPerFrame;		// ������ ��� �ð�

	//===================================================================================
	// Frame Time
	//===================================================================================
	LARGE_INTEGER	m_FPS;					// FPS üũ Ÿ�̸�
	int				m_iFramePerSecond;		// �ʴ� ������
	int				m_iFPSElapse;			// �ʴ� ����� ������

	//===================================================================================
	//	Event Time
	//===================================================================================
	LARGE_INTEGER	m_Start;				// �̺�Ʈ Ÿ�̸� ���� �ð�
	LARGE_INTEGER	m_Elapse;				// �̺�Ʈ Ÿ�̸� ��� �ð�
	bool			m_bStarted;				// �̺�Ʈ Ÿ�̸� �۵� ����
	float			m_fEventTime;
public:
	//===================================================================================
	//	Frame Work
	//===================================================================================
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release() { return true; }

	//===================================================================================
	// ����� �ð��� ���� ���� �Լ�
	//===================================================================================
	void	Reset();
	void	Start();
	void	Stop();
	bool	IsStarted()const { return m_bStarted; }
	float	GetElapsedTime();

	//===================================================================================
	// FPS
	//===================================================================================
	int		GetFPS() { return m_iFramePerSecond; }
	float	GetSPF() { return m_fSecPerFrame; }

public:
	STimer();
	virtual ~STimer();
};

class SGrobalTimer : public Singleton<SGrobalTimer>
{
private:
	friend class Singleton<SGrobalTimer>;
private:
	STimer m_Timer;
	//===================================================================================
	// Debug Render
	//===================================================================================
	D3DXVECTOR2 m_vStart;
	D3DXVECTOR2 m_vEnd;

	bool m_bDebugFlag;
	UINT m_iClientHeight;
	UINT m_iClientWidth;
public:
	
	//===================================================================================
	//	Frame Work
	//===================================================================================
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release() { return true; }

	//===================================================================================
	// ����� �ð��� ���� ���� �Լ�
	//===================================================================================
	void	Reset() { m_Timer.Reset();} ;
	void	Start() { m_Timer.Start(); };
	void	Stop() { m_Timer.Stop(); };
	bool	IsStarted()const { return m_Timer.IsStarted(); }
	float	GetElapsedTime() { return m_Timer.GetElapsedTime(); }

	//===================================================================================
	// FPS
	//===================================================================================
	int		GetFPS() { return m_Timer.GetFPS(); }
	float	GetSPF() { return m_Timer.GetSPF(); }

	//===================================================================================
	// Debug Render
	//===================================================================================
	void	SetDebugFlag(bool bFlag) { m_bDebugFlag = bFlag; };
	void	SetDebugRect(D3DXVECTOR2 vStart, D3DXVECTOR2 vEnd);
private:
	SGrobalTimer() {} ;
public:
	virtual ~SGrobalTimer() {} ;
};

#define I_Timer SGrobalTimer::GetInstance()

