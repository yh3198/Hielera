#pragma once
#include "BScene.h"

class BLobbyScene : public BScene
{
public:
	bool Init();
	DWORD Frame();
	bool Render(HDC hOffScreenDC);
	bool Release();
public:
	RECT m_Yes;
	RECT m_No;
	RECT m_ID;
	RECT m_PW;
public:
	BLobbyScene();
	~BLobbyScene();
};

