#pragma once
#include "BObjectMgr.h"


struct BRectUV
{
	RECT rt;
	RECT rtSrc;
};

class BSprite : public BObject
{
public:
	vector<BRectUV*> m_RectList;
	int m_iApplyIndex;
	float m_fSecPerRender;
	float m_fTime;
	float m_fLifeTime;
	
	int m_iIndex; // ÃÑ ºñÆ®¸Ê ¼ö
	int	m_iNumBitmap; // ÇöÀç ºñÆ®¸Ê

public:
	bool ComboUpdate(TCHAR ComboNum);
	bool Update(BPOINT Setpos);
	bool Reset();

public:
	BSprite();
	~BSprite();
};

