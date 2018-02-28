#pragma once
#include "BLobbyScene.h"
#include "BGameScene.h"
#include "BResultScene.h"


class BSceneMgr
{
public:
	map < DWORD, BScene*> BSceneMap;
	BScene* GetScene(DWORD SceneNum);

public:
	BSceneMgr();
	~BSceneMgr();
};

