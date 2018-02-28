#pragma once
#include "BSprite.h"

class BSpriteMgr
{
public:
	int m_iSpIndex;
	map<int, BSprite*> m_SpMapList;
	RECT rt[20];
	RECT rtSrc[20];

public:

	static BSpriteMgr& GetInstance()
	{
		static BSpriteMgr singleton;
		return singleton;
	}

	int LoadSp(TCHAR* objName, TCHAR* fileName, TCHAR* MaskfileName, RECT rtDesc, RECT rtSrc, float posX, float posY, int SpIndex, TCHAR* pszSpriteName, float Lifetime);
	bool RectInfoCreate(TCHAR* pszSpriteName, int iIndex);
	bool GetSp(HDC hDC, int iIndex, BPOINT SetPos, bool& Playing);
	bool GetCombo(HDC hDC, int Combo);

    //bool DeleteSp(int iIndex);
	

	BSprite* GetSpPtr(int iIndex);
	

	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	BSpriteMgr();
	~BSpriteMgr();
};

#define I_SpmapMgr BSpriteMgr::GetInstance()