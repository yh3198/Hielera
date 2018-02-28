#include "BSpriteMgr.h"

bool BSpriteMgr::Init()
{
	for (int iCnt = 0; iCnt < 5; iCnt++)
	{
		rt[iCnt].left = 0;
		rt[iCnt].top = 0;
		rt[iCnt].right = 480;   // right = weight, bottom = height
		rt[iCnt].bottom = 576;

		rtSrc[iCnt].left = 0;
		rtSrc[iCnt].top = 0;
		rtSrc[iCnt].right = 96;
		rtSrc[iCnt].bottom = 96;

		LoadSp(L"NoteClear", L"../../data/NoteClear.bmp", L"../../data/NoteClear_mask.bmp", rt[iCnt], rtSrc[iCnt], 254.0f+(float)(98*iCnt), 903.0f, 27, L"Sprite.txt", 0.5f);
	}

		rt[5].left = 0;
		rt[5].top = 0;
		rt[5].right = 70;   // right = weight, bottom = height
		rt[5].bottom = 70;

		rtSrc[5].left = 0;
		rtSrc[5].top = 0;
		rtSrc[5].right = 70;
		rtSrc[5].bottom = 70;

		LoadSp(L"Number", L"../../data/Number.bmp", L"../../data/Number_mask.bmp", rt[5], rtSrc[5], 415.0f, 200.0f, 10, L"Number.txt", 0.0f); // 5
		
		LoadSp(L"Number", L"../../data/Number.bmp", L"../../data/Number_mask.bmp", rt[5], rtSrc[5], 380.0f, 200.0f, 10, L"Number.txt", 0.0f); // 6
		LoadSp(L"Number", L"../../data/Number.bmp", L"../../data/Number_mask.bmp", rt[5], rtSrc[5], 450.0f, 200.0f, 10, L"Number.txt", 0.0f); // 7

		LoadSp(L"Number", L"../../data/Number.bmp", L"../../data/Number_mask.bmp", rt[5], rtSrc[5], 345.0f, 200.0f, 10, L"Number.txt", 0.0f); // 8
		LoadSp(L"Number", L"../../data/Number.bmp", L"../../data/Number_mask.bmp", rt[5], rtSrc[5], 415.0f, 200.0f, 10, L"Number.txt", 0.0f); // 9
		LoadSp(L"Number", L"../../data/Number.bmp", L"../../data/Number_mask.bmp", rt[5], rtSrc[5], 485.0f, 200.0f, 10, L"Number.txt", 0.0f); // 10

		rt[6].left = 0;
		rt[6].top = 0;
		rt[6].right = 5000;   // right = weight, bottom = height
		rt[6].bottom = 500;

		rtSrc[6].left = 0;
		rtSrc[6].top = 0;
		rtSrc[6].right = 500;
		rtSrc[6].bottom = 500;

		LoadSp(L"Number", L"../../data/Boom.bmp", L"../../data/Boom_mask.bmp", rt[6], rtSrc[6], 450.0f, 500.0f, 10, L"BoomSprite.txt", 0.5f); // 10

	return true;
}

bool BSpriteMgr::RectInfoCreate(TCHAR* pszSpriteName, int iIndex)
{
	TCHAR BBuffer[256] = { 0, };
	FILE* fp_Sprite;
	_wfopen_s(&fp_Sprite, pszSpriteName, _T("rt"));
	if (fp_Sprite == NULL) return false;
	int AllRectCount;
	_fgetts(BBuffer, _countof(BBuffer), fp_Sprite);
	_stscanf_s(BBuffer, _T("%d"), &AllRectCount);
	for (int iCnt = 0; iCnt < AllRectCount; iCnt++)
	{
		BRectUV * pData = new BRectUV();
		_fgetts(BBuffer, _countof(BBuffer), fp_Sprite);
		_stscanf_s(BBuffer, _T("%d %d %d %d %d %d %d %d"), &pData->rt.left, &pData->rt.top, &pData->rt.right, &pData->rt.bottom,
														   &pData->rtSrc.left, &pData->rtSrc.top, &pData->rtSrc.right, &pData->rtSrc.bottom);
		m_SpMapList[iIndex]->m_RectList.push_back(pData);
	}
}

int BSpriteMgr::LoadSp(TCHAR* objName, TCHAR* fileName, TCHAR* MaskfileName, RECT rtDesc, RECT rtSrc, float posX, float posY, int SpIndex, TCHAR* pszSpriteName, float Lifetime)
{
	BSprite * pData = new BSprite();
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
		pData->Bitnum = I_BitmapMgr.Load(fileName);// 오브젝트 로드 불러올 것
		pData->m_iIndex = SpIndex;
		if (MaskfileName)
		{
			pData->MaskBitnum = I_BitmapMgr.Load(MaskfileName);
			pData->m_pBitmapMask = I_BitmapMgr.GetPtr(pData->MaskBitnum);
		}
		pData->m_pBitmap = I_BitmapMgr.GetPtr(pData->Bitnum);
		pData->m_fLifeTime = Lifetime;
		pData->m_fSecPerRender = Lifetime / (float)SpIndex ;

		m_SpMapList.insert(make_pair(m_iSpIndex++, pData));
		RectInfoCreate(pszSpriteName, m_iSpIndex - 1);
	}
	else
	{
		delete pData;
		return -1;
	}
	return m_iSpIndex - 1;
}

bool BSpriteMgr::GetSp(HDC hDC, int m_SpjIndex, BPOINT SetPos, bool& Playing)
{
	if (Playing != false)
	{
		map<int, BSprite*>::iterator itor;
		itor = m_SpMapList.find(m_SpjIndex);
		if (itor == m_SpMapList.end()) return NULL;

		if ((*itor).second->MaskBitnum != NULL)
		{
			BPOINT Drawpos;
			Drawpos.x = itor->second->pos.x - (*itor).second->rtSrc.right / 2;
			Drawpos.y = itor->second->pos.y - (*itor).second->rtSrc.bottom / 2;
			I_BitmapMgr.GetPtr((*itor).second->MaskBitnum)->DrawSRCAND(hDC,
				Drawpos,
				(*itor).second->rt,
				(*itor).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor).second->Bitnum)->DrawSRCINVERT(hDC,
				Drawpos,
				(*itor).second->rt,
				(*itor).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor).second->MaskBitnum)->DrawSRCINVERT(hDC,
				Drawpos,
				(*itor).second->rt,
				(*itor).second->rtSrc);
		}
		else
		{
			BPOINT Drawpos;
			Drawpos.x = itor->second->pos.x - (*itor).second->rtSrc.right / 2;
			Drawpos.y = itor->second->pos.y - (*itor).second->rtSrc.bottom / 2;
			I_BitmapMgr.GetPtr((*itor).second->Bitnum)->BGDraw(hDC,
				Drawpos,
				(*itor).second->rt,
				(*itor).second->rtSrc);
		}
		Playing = (*itor).second->Update(SetPos);
	}
	return true;
}

bool BSpriteMgr::GetCombo(HDC hDC, int Combo)
{
	bool ComboClear;
	if (Combo > 0)
		ComboClear = true;
	else
		ComboClear = false;
	TCHAR ComboString[4];
	_itow_s(Combo, ComboString, 10);
	int ComboCase = wcslen(ComboString);
	map<int, BSprite*>::iterator itor1;
	map<int, BSprite*>::iterator itor2;
	map<int, BSprite*>::iterator itor3;

	switch (ComboCase)
	{
	case 1:
		itor1 = m_SpMapList.find(5);
		if (itor1 == m_SpMapList.end()) return NULL;
		if ((*itor1).second->MaskBitnum != NULL)
		{
			I_BitmapMgr.GetPtr((*itor1).second->MaskBitnum)->DrawSRCAND(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor1).second->Bitnum)->DrawSRCINVERT(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor1).second->MaskBitnum)->DrawSRCINVERT(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
		}
		(*itor1).second->ComboUpdate(ComboString[0]);
		break;
	case 2:
		itor1 = m_SpMapList.find(6);
		if (itor1 == m_SpMapList.end()) return NULL;
		if ((*itor1).second->MaskBitnum != NULL)
		{
			I_BitmapMgr.GetPtr((*itor1).second->MaskBitnum)->DrawSRCAND(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor1).second->Bitnum)->DrawSRCINVERT(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor1).second->MaskBitnum)->DrawSRCINVERT(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
		}
		(*itor1).second->ComboUpdate(ComboString[0]);
		itor2 = m_SpMapList.find(7);
		if (itor2 == m_SpMapList.end()) return NULL;
		(*itor2).second->ComboUpdate(ComboString[1]);
		if ((*itor2).second->MaskBitnum != NULL)
		{
			I_BitmapMgr.GetPtr((*itor2).second->MaskBitnum)->DrawSRCAND(hDC,
				itor2->second->pos,
				(*itor2).second->rt,
				(*itor2).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor2).second->Bitnum)->DrawSRCINVERT(hDC,
				itor2->second->pos,
				(*itor2).second->rt,
				(*itor2).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor2).second->MaskBitnum)->DrawSRCINVERT(hDC,
				itor2->second->pos,
				(*itor2).second->rt,
				(*itor2).second->rtSrc);
		}
		break;
	case 3:
		itor1 = m_SpMapList.find(8);
		if (itor1 == m_SpMapList.end()) return NULL;
		if ((*itor1).second->MaskBitnum != NULL)
		{
			I_BitmapMgr.GetPtr((*itor1).second->MaskBitnum)->DrawSRCAND(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor1).second->Bitnum)->DrawSRCINVERT(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor1).second->MaskBitnum)->DrawSRCINVERT(hDC,
				itor1->second->pos,
				(*itor1).second->rt,
				(*itor1).second->rtSrc);
		}
		(*itor1).second->ComboUpdate(ComboString[0]);
		itor2 = m_SpMapList.find(9);
		if (itor2 == m_SpMapList.end()) return NULL;
		(*itor2).second->ComboUpdate(ComboString[1]);
		if ((*itor2).second->MaskBitnum != NULL)
		{
			I_BitmapMgr.GetPtr((*itor2).second->MaskBitnum)->DrawSRCAND(hDC,
				itor2->second->pos,
				(*itor2).second->rt,
				(*itor2).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor2).second->Bitnum)->DrawSRCINVERT(hDC,
				itor2->second->pos,
				(*itor2).second->rt,
				(*itor2).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor2).second->MaskBitnum)->DrawSRCINVERT(hDC,
				itor2->second->pos,
				(*itor2).second->rt,
				(*itor2).second->rtSrc);
		}
		itor3 = m_SpMapList.find(10);
		if (itor3 == m_SpMapList.end()) return NULL;
		(*itor3).second->ComboUpdate(ComboString[2]);
		if ((*itor3).second->MaskBitnum != NULL)
		{
			I_BitmapMgr.GetPtr((*itor2).second->MaskBitnum)->DrawSRCAND(hDC,
				itor3->second->pos,
				(*itor3).second->rt,
				(*itor3).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor3).second->Bitnum)->DrawSRCINVERT(hDC,
				itor3->second->pos,
				(*itor3).second->rt,
				(*itor3).second->rtSrc);
			I_BitmapMgr.GetPtr((*itor3).second->MaskBitnum)->DrawSRCINVERT(hDC,
				itor3->second->pos,
				(*itor3).second->rt,
				(*itor3).second->rtSrc);
		}
		break;
	default:
		break;
	}
	return true;
}



BSprite* BSpriteMgr::GetSpPtr(int iIndex)
{
	map<int, BSprite*>::iterator itor;
	itor = m_SpMapList.find(iIndex);
	if (itor == m_SpMapList.end())return NULL;
	return (BSprite*)(*itor).second;
}


bool BSpriteMgr::Frame()
{
	return true;
}
bool BSpriteMgr::Render()
{
	return true;
}
bool BSpriteMgr::Release()
{
	m_SpMapList.clear();
	return true;
}

BSpriteMgr::BSpriteMgr()
{
	m_iSpIndex = 0;
}


BSpriteMgr::~BSpriteMgr()
{
}
