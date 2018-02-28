#pragma once
#include "BSceneMgr.h"

class Sample : public BCore
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void GetScene();

public:
	BSceneMgr BpScene;
	DWORD NowScene;

public:
	Sample();
	~Sample();
};