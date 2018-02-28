#include "BSceneMgr.h"

BScene* BSceneMgr::GetScene(DWORD SceneNum)
{
	return BSceneMap[SceneNum];
}

BSceneMgr::BSceneMgr()
{
	BSceneMap[Lobby] = new BLobbyScene;
	BSceneMap[Game] = new BGameScene;
	BSceneMap[Result] = new BResultScene;
}


BSceneMgr::~BSceneMgr()
{
}