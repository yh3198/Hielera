#include "BObjectMgr.h"

int BObjectMgr::LoadObj(TCHAR* objName, TCHAR* fileName, TCHAR* MaskfileName, RECT rtDesc, RECT rtSrc, float posX, float posY)
{
	BObject * pData = new BObject();
	if (pData != NULL)
	{
		pData->objName = objName;
		pData->rt = rtDesc;
		pData->rtSrc = rtSrc;
		pData->pos.x = posX;
		pData->pos.y = posY;
		pData->col_rt.left = posX;
		pData->col_rt.top = posY;
		pData->col_rt.right = rtSrc.right;
		pData->col_rt.bottom = rtSrc.bottom;
		pData->Bitnum = I_BitmapMgr.Load(fileName);   // 오브젝트 로드 불러올 것
		if (MaskfileName)
		{
			pData->MaskBitnum = I_BitmapMgr.Load(MaskfileName);
			pData->m_pBitmapMask = I_BitmapMgr.GetPtr(pData->MaskBitnum);
		}
		pData->m_pBitmap = I_BitmapMgr.GetPtr(pData->Bitnum);
		m_ObjMapList.insert(make_pair(m_iObjIndex++, pData));
	}
	else
	{
		delete pData;
		return -1;
	}
	return m_iObjIndex - 1;
}

bool BObjectMgr::GetOBj(HDC hDC, int m_iObjIndex)
{
	map<int, BObject*>::iterator itor;
	itor = m_ObjMapList.find(m_iObjIndex);
	if (itor == m_ObjMapList.end()) return NULL;
	
	if ((*itor).second->MaskBitnum != NULL)
	{
		I_BitmapMgr.GetPtr((*itor).second->MaskBitnum)->DrawSRCAND(hDC,
			itor->second->pos,
			(*itor).second->rt,
			(*itor).second->rtSrc);
		I_BitmapMgr.GetPtr((*itor).second->Bitnum)->DrawSRCINVERT(hDC,
			itor->second->pos,
			(*itor).second->rt,
			(*itor).second->rtSrc);
		I_BitmapMgr.GetPtr((*itor).second->MaskBitnum)->DrawSRCINVERT(hDC,
			itor->second->pos,
			(*itor).second->rt,
			(*itor).second->rtSrc);
	}
	else
	{
		I_BitmapMgr.GetPtr((*itor).second->Bitnum)->BGDraw(hDC,
			itor->second->pos,
			(*itor).second->rt,
			(*itor).second->rtSrc);
	}
	return true;
}

BObject* BObjectMgr::GetObjPtr(int iIndex)
{
	map<int, BObject*>::iterator itor;
	itor = m_ObjMapList.find(iIndex);
	if (itor == m_ObjMapList.end())return NULL;
	return (BObject*)(*itor).second;
}

bool BObjectMgr::DeleteObj(int iIndex)
{
	m_ObjMapList.erase(iIndex);
	return true;
}

bool BObjectMgr::Init(float HeroX, float HeroY)
{
	rt[0].left = 0;
	rt[0].top = 0;
	rt[0].right = 1000;   // right = weight, bottom = height
	rt[0].bottom = 1000;

	rtSrc[0].left = 0;
	rtSrc[0].top = 0;
	rtSrc[0].right = 1000;
	rtSrc[0].bottom = 1000;

	LoadObj(L"title", L"../../data/title.bmp", NULL , rt[0], rtSrc[0], 0.0f, 0.0f);

	rt[1].left = 0;
	rt[1].top = 0;
	rt[1].right = 103;   // right = weight, bottom = height
	rt[1].bottom = 36;

	rtSrc[1].left = 0;
	rtSrc[1].top = 0;
	rtSrc[1].right = 103;
	rtSrc[1].bottom = 36;

	LoadObj(L"Yes", L"../../data/Yes.bmp", L"../../data/Yes_mask.bmp", rt[1], rtSrc[1], 391.0f, 777.0f);
	LoadObj(L"Yes_Selcet", L"../../data/Yes_Select.bmp", L"../../data/Yes_Select_mask.bmp", rt[1], rtSrc[1], 391.0f, 777.0f);

	rt[2].left = 0;
	rt[2].top = 0;
	rt[2].right = 103;   // right = weight, bottom = height
	rt[2].bottom = 36;

	rtSrc[2].left = 0;
	rtSrc[2].top = 0;
	rtSrc[2].right = 103;
	rtSrc[2].bottom = 36;

	LoadObj(L"No", L"../../data/No.bmp", L"../../data/No_mask.bmp", rt[2], rtSrc[2], 511.0f, 777.0f);
	LoadObj(L"No_Select", L"../../data/No_Select.bmp", L"../../data/No_Select_mask.bmp", rt[2], rtSrc[2], 511.0f, 777.0f);

	rt[3].left = 0;
	rt[3].top = 0;
	rt[3].right = 700;   // right = weight, bottom = height
	rt[3].bottom = 1000;

	rtSrc[3].left = 0;
	rtSrc[3].top = 0;
	rtSrc[3].right = 700;
	rtSrc[3].bottom = 1000;

	LoadObj(L"main", L"../../data/Main.bmp", L"../../data/Main_mask.bmp", rt[3], rtSrc[3], 100.0f, 0.0f);

	
	rt[4].left = 0;
	rt[4].top = 0;
	rt[4].right = 100;   // right = weight, bottom = height
	rt[4].bottom = 100;

	rtSrc[4].left = 0;
	rtSrc[4].top = 0;
	rtSrc[4].right = 100;
	rtSrc[4].bottom = 100;
	
	for (int BombCount = 0; BombCount < 3; BombCount++)
	{
		LoadObj(L"Bomb", L"../../data/Bomb.bmp", L"../../data/Bomb_mask.bmp", rt[4], rtSrc[4], 856.0f, 630.0f + 120*BombCount);
	}

	rt[5].left = 0;
	rt[5].top = 0;
	rt[5].right = 200;   // right = weight, bottom = height
	rt[5].bottom = 200;

	rtSrc[5].left = 0;
	rtSrc[5].top = 0;
	rtSrc[5].right = 200;
	rtSrc[5].bottom = 200;

	LoadObj(L"CDcover", L"../../data/CDcover.bmp", NULL, rt[5], rtSrc[5], 768.0f, 114.0f);

	rt[6].left = 0;
	rt[6].top = 0;
	rt[6].right = 90;   // right = weight, bottom = height
	rt[6].bottom = 30;

	rtSrc[6].left = 0;
	rtSrc[6].top = 0;
	rtSrc[6].right = 90;
	rtSrc[6].bottom = 30;

	for (int buttonCount = 0; buttonCount < 5; buttonCount++)
	{
		LoadObj(L"Button_normal", L"../../data/Button_normal.bmp", L"../../data/Button_normal_mask.bmp", rt[6], rtSrc[6], 209.0f + buttonCount * 98, 888.0f);
	}

	for (int buttonCount = 0; buttonCount < 5; buttonCount++)
	{
		LoadObj(L"Button_push", L"../../data/Button_push.bmp", L"../../data/Button_push_mask.bmp", rt[6], rtSrc[6], 209.0f + buttonCount * 98, 888.0f);
	}

	rt[7].left = 0;
	rt[7].top = 0;
	rt[7].right = 1000;   // right = weight, bottom = height
	rt[7].bottom = 1000;

	rtSrc[7].left = 0;
	rtSrc[7].top = 0;
	rtSrc[7].right = 1000;
	rtSrc[7].bottom = 1000;

	LoadObj(L"Result", L"../../data/Result.bmp", NULL, rt[7], rtSrc[7], 0.0f, 0.0f);

	rt[8].left = 0;
	rt[8].top = 0;
	rt[8].right = 90;   // right = weight, bottom = height
	rt[8].bottom = 30;

	rtSrc[8].left = 0;
	rtSrc[8].top = 0;
	rtSrc[8].right = 90;
	rtSrc[8].bottom = 30;
	
	LoadObj(L"Note", L"../../data/Note.bmp", L"../../data/Note_mask.bmp", rt[8], rtSrc[8], 209.0f , 50.0f);

	rt[9].left = 0;
	rt[9].top = 0;
	rt[9].right = 250;   // right = weight, bottom = height
	rt[9].bottom = 100;

	rtSrc[9].left = 0;
	rtSrc[9].top = 0;
	rtSrc[9].right = 250;
	rtSrc[9].bottom = 100;

	LoadObj(L"Perfect", L"../../data/Perfect.bmp", L"../../data/Perfect_mask.bmp", rt[9], rtSrc[9], 320.0f , 100.0f);
	LoadObj(L"Great", L"../../data/Great.bmp", L"../../data/Great_mask.bmp", rt[9], rtSrc[9], 320.0f, 100.0f);
	LoadObj(L"Good", L"../../data/Good.bmp", L"../../data/Good_mask.bmp", rt[9], rtSrc[9], 320.0f, 100.0f);
	LoadObj(L"Bad", L"../../data/Bad.bmp", L"../../data/Bad_mask.bmp", rt[9], rtSrc[9], 320.0f, 100.0f);
	LoadObj(L"Miss", L"../../data/Miss.bmp", L"../../data/Miss_mask.bmp", rt[9], rtSrc[9], 320.0f, 100.0f);

	rt[10].left = 0;
	rt[10].top = 0;
	rt[10].right = 1000;   // right = weight, bottom = height
	rt[10].bottom = 1000;

	rtSrc[10].left = 0;
	rtSrc[10].top = 0;
	rtSrc[10].right = 1000;
	rtSrc[10].bottom = 1000;
	LoadObj(L"BG_back", L"../../data/BG_back.bmp", NULL, rt[10], rtSrc[10], 0.0f, 0.0f);


	return true;
}
bool BObjectMgr::Frame()
{
	return true;
}
bool BObjectMgr::Render()
{
	return true;
}
bool BObjectMgr::Release()
{
	m_ObjMapList.clear();
	return true;
}

BObjectMgr::BObjectMgr()
{
	m_NpcCount = 12;
}


BObjectMgr::~BObjectMgr()
{
}
