#include "BCore.h"

bool g_GameClose = false;

bool BCore::BInit(int BWidth, int BHeight)
{
	m_hScreenDC = GetDC(g_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	HBITMAP m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, BWidth, BHeight);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	I_SoundMgr.Init();
	I_TimerMgr.Init();
	m_DefaultFont = CreateFont(20, 0, 0, FW_BOLD, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, 0, L"a아띠");
	SelectObject(m_hOffScreenDC, m_DefaultFont);
	I_InputMgr.Init();
	I_ObjmapMgr.Init(HeroX, HeroY);
	I_SpmapMgr.Init();
	Init();
	SetBkColor(m_hOffScreenDC, RGB(255, 0, 0));
	SetTextColor(m_hOffScreenDC, RGB(0, 0, 0));
	SetBkMode(m_hOffScreenDC, TRANSPARENT); // 투명하게 
	return true;
}
bool BCore::BFrame()
{
	I_TimerMgr.Frame();
	I_InputMgr.Frame();
	I_SoundMgr.m_pSystem->update();
	Frame();
	return true;
}
bool BCore::BRender(int BWidth, int BHeight)
{

	BPreRender(BWidth, BHeight);
		Render();
	BPostRender(BWidth, BHeight);
	
	return true;
}

bool BCore::BPreRender(int BWidth, int BHeight)
{
	PatBlt(m_hOffScreenDC, 0, 0, BWidth, BHeight, PATCOPY); // 색을 전부 채워라
	return true;
}

bool BCore::BPostRender(int BWidth, int BHeight)
{
	BitBlt(m_hScreenDC, 0, 0, BWidth, BHeight, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

bool BCore::BRelease()
{
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	SelectObject(m_hOffScreenDC, m_hOldBrush);
	DeleteObject(m_hbrBack);

	ReleaseDC(g_hWnd, m_hOffScreenDC);
	ReleaseDC(g_hWnd, m_hScreenDC);
	I_SoundMgr.Release();
	I_TimerMgr.Release();
	I_InputMgr.Release();
	I_BitmapMgr.Release();
	I_ObjmapMgr.Release();
	DeleteObject(m_DefaultFont);
	Release();
	
	
	return true;
}

bool BCore::Init()
{
	return true;
}
bool BCore::Frame()
{
	return true;
}
bool BCore::Render()
{
	return true;
}
bool BCore::Release()
{
	return true;
}


bool BCore::Run(int BWidth, int BHeight)
{
	BInit(BWidth, BHeight);
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT && g_GameClose != true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			BFrame ();
			BRender(BWidth, BHeight);
		}
	}
	BRelease();
	return true;
}

LRESULT BCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	I_InputMgr.MsgProc(hWnd, msg, wParam, lParam);
	return 0;
}


BCore::BCore()
{
	SceneKey = 0;
	HeroX = 0.0f;
	HeroY = 0.0f;
}


BCore::~BCore()
{
}
