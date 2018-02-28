#include "BSprite.h"



bool BSprite::Update(BPOINT Setpos)
{
	m_fTime += g_fSecPerFrame;
	if (m_fTime >= m_fSecPerRender)
	{
		if (m_iNumBitmap != m_iIndex)
		{
			rt = m_RectList[m_iNumBitmap]->rt;
			rtSrc = m_RectList[m_iNumBitmap]->rtSrc;
			pos = Setpos;
			m_fTime = 0;
			m_iNumBitmap++;
		}
		else
		{
			m_iNumBitmap = 0;
			rt = m_RectList[m_iNumBitmap]->rt;
			rtSrc = m_RectList[m_iNumBitmap]->rtSrc;
			pos = Setpos;
			m_fTime = 0;
			return false;
		}
	}
	return true;
}

bool BSprite::ComboUpdate(TCHAR ComboNum)
{
	int Combo = ComboNum-48;
	rt = m_RectList[Combo]->rt;
	rtSrc = m_RectList[Combo]->rtSrc;
	return true;
}

bool BSprite::Reset()
{
	m_iNumBitmap = 0;
	return true;
}

BSprite::BSprite()
{
	m_fTime = 0;
	m_iNumBitmap = 0;
}


BSprite::~BSprite()
{
	m_RectList.clear();
}
