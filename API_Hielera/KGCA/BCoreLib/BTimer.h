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
	/* 계산의 필수요소 */
	float m_fElapseTick;  // 플레이시간
	float m_fSecPerFrame; // 1프레임의 경과시간
	DWORD m_dwFPS;		  // 1초에 프레임 호출 개수

						  /* 위의 요소를 구하기 위한 Temp */
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
