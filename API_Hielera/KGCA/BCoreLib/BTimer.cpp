#include "BTimer.h"

float g_fSecPerFrame = 0.0f;

bool BTimer::Init()
{
	m_dwBeforeTick = timeGetTime(); // ƽ�̶�� �ð������� ����
	ZeroMemory(m_csBuffer, sizeof(TCHAR)*MAX_PATH); // ȭ��� �Ź� ���
	return true;
}
bool BTimer::Frame()
{
	DWORD dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;


	m_fSecPerFrame = dwElapseTick / 1000.0f; // õƽ�� ������ 1�ʰ� ������
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
	m_dwBeforeTick = dwCurrentTick; // FPS (FRAME PER SEC)�� üũ, 1FRAME�� ���ư� �ð�

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
