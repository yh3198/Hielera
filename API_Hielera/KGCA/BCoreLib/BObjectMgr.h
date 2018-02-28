#pragma once
#include "BObject.h"

class BObjectMgr
{
public:
	int m_iObjIndex;
	map<int, BObject*> m_ObjMapList;
	int m_NpcCount;
	RECT rt[20];
	RECT rtSrc[20];

public:
	static BObjectMgr& GetInstance()
	{
		static BObjectMgr singleton;
		return singleton;
	}
	
	bool DeleteObj(int iIndex);
	int LoadObj(TCHAR* objName, TCHAR* fileName, TCHAR* MaskfileName, RECT rtDesc, RECT rtSrc, float posX, float posY);

	BObject* GetObjPtr(int iIndex);
	bool GetOBj(HDC hDC, int iIndex);
	/*bool RotateBlt(HDC hDC, HDC offhDC, int iIndex, float fAngle);
	HBITMAP GetRotatedBitmap(HDC hDC, float fAngle, int Width, int Height, RECT SrcRt);*/
	//bool GetOBjTrans(HDC hDC, int m_iObjIndex);
	
	bool Init(float HeroX, float HeroY);
	bool Frame();
	bool Render();
	bool Release();
	


private:
	BObjectMgr();
public:
	~BObjectMgr();
};

#define I_ObjmapMgr BObjectMgr::GetInstance()