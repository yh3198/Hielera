#pragma once
#include "BScene.h"

class BResultScene : public BScene
{
public:
	TCHAR m_csBuffer[MAX_PATH];
	HFONT m_DefaultFont;
public:
	bool Init();
	DWORD Frame();
	bool Render(HDC hOffScreenDC);
	bool Release();
public:
	BResultScene();
	~BResultScene();
};

