#pragma once
#include "BScene.h"

class BGameScene : public BScene
{
public:
	bool Init();
	DWORD Frame();
	bool Render(HDC hOffScreenDC);
	bool Release();
	bool GamePointdraw(int GamePoint);
	int NoteAccuracyCheck(int Gamepoint);

public:
	float BPlayTime;
	int MissCheck;
	int GamePoint;
	int TotalGamePoint;
	int Combo;
	int NoteAccuracy;
	TCHAR m_csBuffer[MAX_PATH];
	bool SpPlaying_1;
	bool SpPlaying_2;
	bool SpPlaying_3;
	bool SpPlaying_4;
	bool SpPlaying_5;
	bool SpPlaying_6;
	bool ComboSpeedCheck;
	int BombCount;
	int NBottonCount;

public:
	BGameScene();
	~BGameScene();
};

