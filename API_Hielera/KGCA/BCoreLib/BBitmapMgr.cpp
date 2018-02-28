#include "BBitmapMgr.h"




int BBitmapMgr::Load(TCHAR* fileName)
{
	map<int, BBitmap*>::iterator itor;
	for (itor = m_MapList.begin(); itor != m_MapList.end(); itor++)
	{
		BBitmap* pData = (*itor).second;
		if (pData->m_szName == fileName)
		{
			return (*itor).first;
		}
	}
	BBitmap *  pData = new BBitmap;
	if (pData != NULL)
	{
		pData->m_szName = fileName;
		if (pData->Load(fileName))
		{
			m_MapList.insert(make_pair(m_iIndex++, pData));
		}
		else
		{
			delete pData;
			return -1;
		}
	}
	return m_iIndex - 1;
}

BBitmap* BBitmapMgr::GetPtr(int iIndex)
{
	map<int, BBitmap*>::iterator itor;
	itor = m_MapList.find(iIndex);
	if (itor == m_MapList.end()) return NULL;
	return (BBitmap*)(*itor).second;
}

bool BBitmapMgr::Release()
{
	m_MapList.clear();
	return true;
}

BBitmapMgr::BBitmapMgr()
{
	m_iIndex = 0;
}


BBitmapMgr::~BBitmapMgr()
{
}

