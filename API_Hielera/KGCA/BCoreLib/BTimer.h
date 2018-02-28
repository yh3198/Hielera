#pragma once
#include "BStd.h"

class BTimer
{
public:
	static BTimer& GetInstance()
	{
		static BTimer singleton;
		return singleton;
	}
	/* ����� �ʼ���� */
	float m_fElapseTick;  // �÷��̽ð�
	float m_fSecPerFrame; // 1�������� ����ð�
	DWORD m_dwFPS;		  // 1�ʿ� ������ ȣ�� ����

						  /* ���� ��Ҹ� ���ϱ� ���� Temp */
	DWORD m_dwBeforeTick;
	float m_fFrameTime;
	DWORD m_dwFrameCount;

	TCHAR m_csBuffer[MAX_PATH];


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	BTimer();
	~BTimer();
};

#define I_TimerMgr BTimer::GetInstance()
