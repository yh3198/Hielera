#pragma once
#include "BStd.h"

class BBitmap
{
public:
	wstring m_szName;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	HDC m_hMemDC;
	BLENDFUNCTION Alpha;
	int m_iAlpha;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(TCHAR* pszLoadFile);
	bool DrawSRCAND(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc);
	bool DrawSRCINVERT(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc);
	bool DrawAlphaBlend(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc);
	bool BGDraw(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc);
	/*bool DrawTrans(HDC hDC, BPOINT pos, RECT rtDesc, RECT rtSrc);*/

public:
	BBitmap();
	~BBitmap();
};

