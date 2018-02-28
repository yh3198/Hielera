#pragma once
#include "BBitmapMgr.h"


class BObject
{
public:
	RECT col_rt;
	RECT rt;
	RECT rtSrc;
	TCHAR* objName;
	BPOINT pos;
	int m_DirectionX;
	int m_DirectionY;
	int m_fSpeed;
	int Bitnum;
	int MaskBitnum = NULL;

	BBitmap*	m_pBitmap;
	BBitmap*	m_pBitmapMask;


public:
	bool NpcMove();
	bool movePosition(float posX, float posY);

public:
	BObject();
	~BObject();
};

