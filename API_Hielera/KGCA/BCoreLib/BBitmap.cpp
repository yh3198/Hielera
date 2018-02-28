#include "BBitmap.h"

bool BBitmap::DrawAlphaBlend(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc)
{
	Alpha.BlendOp = AC_SRC_OVER;
	Alpha.AlphaFormat = AC_SRC_OVER;
	Alpha.BlendFlags = 0;
	Alpha.SourceConstantAlpha = m_iAlpha;
	AlphaBlend(hDC, pos.x, pos.y, rtDesc.right, rtDesc.bottom, m_hMemDC, rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom, Alpha);
	return true;
}

bool BBitmap::Load(TCHAR* pszLoadFile)
{
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pszLoadFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (m_hBitmap == NULL) return false;
	HDC hScreenDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	ReleaseDC(g_hWnd, hScreenDC);
	return true;
}

bool BBitmap::BGDraw(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc)
{
	if (this != NULL)
	{
		StretchBlt(hDC, pos.x, pos.y, rtDesc.right, rtDesc.bottom, m_hMemDC, rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom, SRCCOPY);
	}
	return true;
}

bool BBitmap::DrawSRCAND(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc)
{
	if (this != NULL)
	{
		StretchBlt(hDC, pos.x, pos.y, rtDesc.right, rtDesc.bottom, m_hMemDC, rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom, SRCAND);
	}
	return true;
}

bool BBitmap::DrawSRCINVERT(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc)
{
	if (this != NULL)
	{
		StretchBlt(hDC, pos.x, pos.y, rtDesc.right, rtDesc.bottom, m_hMemDC, rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom, SRCINVERT);
	}
	return true;
}

bool BBitmap::Init()
{
	return true;
}
bool BBitmap::Render()
{
	return true;
}
bool BBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	ReleaseDC(g_hWnd, m_hMemDC); // 지정된 윈도우의 DC를 반환한다.
	return true;
}
bool BBitmap::Frame()
{
	return true;
}

BBitmap::BBitmap()
{
	m_iAlpha = 127;
}


BBitmap::~BBitmap()
{
}
