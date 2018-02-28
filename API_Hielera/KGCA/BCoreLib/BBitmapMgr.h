#pragma once
#include "BBitmap.h"

class BBitmapMgr
{
public:
	static BBitmapMgr& GetInstance()
	{
		static BBitmapMgr singleton;
		return singleton;
	}
	int Load(TCHAR* fileName);
	BBitmap* GetPtr(int iIndex);
	bool Release();

public:
	int m_iIndex;
	map<int, BBitmap*> m_MapList;

private:
	BBitmapMgr();
public:
	~BBitmapMgr();
};

#define I_BitmapMgr BBitmapMgr::GetInstance()

