#include "BTimer.h"

float g_fSecPerFrame = 0.0f;

bool BTimer::Init()
{
	m_dwBeforeTick = timeGetTime(); // 틱이라는 시간단위를 리턴
	ZeroMemory(m_csBuffer, sizeof(TCHAR)*MAX_PATH); // 화면상에 매번 출력
	return true;
}
bool BTimer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;


	m_fSecPerFrame = dwElapseTick / 1000.0f; // 천틱이 지나면 1초가 지난것
	m_fFrameTime += m_fSecPerFrame;
	m_fElapseTick += m_fSecPerFrame;
	g_fSecPerFrame = m_fSecPerFrame;

	if (m_fFrameTime > 1.0f)
	{
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fFrameTime -= 1.0f;
	}
	m_dwFrameCount++;
	m_dwBeforeTick = dwCurrentTick; // FPS (FRAME PER SEC)를 체크, 1FRAME에 돌아간 시간

	return true;
}
bool BTimer::Render()
{
	return true;
}
bool BTimer::Release()
{
	return true;
}

BTimer::BTimer()
{
	m_fFrameTime = 0.0f;
	m_dwFrameCount = 0;
	m_fElapseTick = 0;
}


BTimer::~BTimer()
{
}
