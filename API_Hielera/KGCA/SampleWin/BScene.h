#pragma once
#include "BCore.h"

enum SceneNum{
	Lobby = 0,
	Game,
	Result,
};

class BScene
{
public:
	virtual bool Init() = 0;
	virtual DWORD Frame() = 0;
	virtual bool Render(HDC hOffScreenDC) = 0;
	virtual bool Release() = 0;
	virtual bool GamePointdraw() { return true; };
	virtual int NoteAccuracyCheck() { return 0; };
public:
	BScene();
	virtual ~BScene();
};

