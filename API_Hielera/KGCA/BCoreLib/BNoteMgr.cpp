#include "BNoteMgr.h"

bool BNoteMgr::AllClearNote(int& Combo, int& GamePoint)
{
	Combo += m_DrawNoteMapList.size();
	int Note = 0;
	while (m_DrawNoteMapList[Note]->NoteType != 0)
	{
		Note++;
	}
	Combo -= Note;

	GamePoint += m_DrawNoteMapList.size()*100;
	m_DrawNoteMapList.clear();
	if (Combo > 100)
	{
		return true;
	}
	return false;
}

bool BNoteMgr::CreateNote(TCHAR* pszLoad)
{
	TCHAR BBuffer[256] = { 0, };

	FILE* fp_Note;
	_wfopen_s(&fp_Note, pszLoad, _T("rt"));
	if (fp_Note == NULL) return false;
	int AllNoteCount;
	_fgetts(BBuffer, _countof(BBuffer), fp_Note);
	_stscanf_s(BBuffer, _T("%d"), &AllNoteCount);
	for (int iCnt = 0; iCnt < AllNoteCount; iCnt++)
	{
		_fgetts(BBuffer, _countof(BBuffer), fp_Note);
		BNote* bTemp = new BNote();
		_stscanf_s(BBuffer, _T("%f %d %d %f"), &bTemp->Notetime, &bTemp->LineNum, &bTemp->NoteType, &bTemp->NoteHeight);
		RECT rt;
		RECT rtRsc;
		BPOINT pos;
		BPOINT Cpos;
		rt.left = 209 + (bTemp->LineNum - 1) * 98;
		rt.top = 50;
		rt.right = 90;
		rt.bottom = 30;
		rtRsc.left = 0;
		rtRsc.top = 0;
		rtRsc.right = 90;
		rtRsc.bottom = 30;
		pos.x = 209 + (bTemp->LineNum - 1) * 98;
		pos.y = 50;
		Cpos.x = pos.x / 2;
		Cpos.y = pos.y / 2;

		bTemp->Position = pos;
		bTemp->rt = rt;
		bTemp->rtRsc = rtRsc;
		bTemp->NoteSpeed = 400.0f;
		bTemp->CenterPosition = Cpos;
		m_NoteMapList.push_back(bTemp);
	}
	return true;
}

bool BNoteMgr::CheckNote(float MusicPlaytime, bool ComboSpeedCheck)
{
	int musictemp = MusicPlaytime * 100;
	float musictime = (float)musictemp / 100;
	
	if (m_NoteMapList.size() != 0)
	{
		BNote* bTemp = new BNote();
		bTemp = m_NoteMapList.front();
		if (ComboSpeedCheck == true)
		{
			bTemp->NoteSpeed = 600.0f;
			bTemp->Position.y = -369.0f;
		}
		if (bTemp->Notetime>musictime-0.03 && bTemp->Notetime<musictime+0.03)
		{
			m_DrawNoteMapList.push_back(bTemp);
			m_NoteMapList.pop_front();
		}
	}
	return true;
}

bool BNoteMgr::DrawNote(HDC hOffScreenDC, int& Combo, int& NoteAccuracy, bool& ComboSpeedCheck, int& MissCheck)
{
	if (m_DrawNoteMapList.size() != 0)
	{
		for (int Note = 0; Note < m_DrawNoteMapList.size(); Note++)
		{
			I_BitmapMgr.GetPtr(19)->DrawSRCAND(hOffScreenDC, m_DrawNoteMapList[Note]->Position, m_DrawNoteMapList[Note]->rt, m_DrawNoteMapList[Note]->rtRsc);
			
			m_DrawNoteMapList[Note]->Position.y += m_DrawNoteMapList[Note]->NoteSpeed * g_fSecPerFrame;
			m_DrawNoteMapList[Note]->CenterPosition.y = m_DrawNoteMapList[Note]->Position.y / 2;
			if (m_DrawNoteMapList[Note]->Position.y > 1000)
			{
				delete m_DrawNoteMapList[Note];
				Combo = 0;
				ComboSpeedCheck = NoteSpeedContral(Combo);
				NoteAccuracy = Miss;
				MissCheck++;
			}
		}
	}
	return true;
}

bool BNoteMgr::NoteSpeedContral(int Combo)
{
	if (Combo == 100)
	{
		return true;
	}
	if (Combo == 0)
	{
		return false;
	}
}

int BNoteMgr::NoteCol(int KeyNum, int& NoteAccuracy, int& Combo, bool& ComboSpeedCheck)
{
	if (m_DrawNoteMapList.size() != 0)
	{
		for (int Note = 0; Note < m_DrawNoteMapList.size(); Note++)
		{
			if (m_DrawNoteMapList[Note]->LineNum == KeyNum)
			{
				RECT rt;
				rt.left = m_DrawNoteMapList[Note]->Position.x;
				rt.top = m_DrawNoteMapList[Note]->Position.y;
				rt.right = m_DrawNoteMapList[Note]->rt.right;
				rt.bottom = m_DrawNoteMapList[Note]->rt.bottom;
				if (I_Collision.SphereInSphere(rt, I_ObjmapMgr.GetObjPtr(9 + KeyNum)->col_rt) == TRUE)
				{
					if (I_Collision.RectInRect(rt, I_ObjmapMgr.GetObjPtr(9 + KeyNum)->col_rt) == TRUE)
					{
						int Point = I_Collision.BCrashsize(rt, I_ObjmapMgr.GetObjPtr(9 + KeyNum)->col_rt);
						delete m_DrawNoteMapList[Note];
						Combo++;
						return Point;
					}
					Combo = 0;
					ComboSpeedCheck = NoteSpeedContral(Combo);
					NoteAccuracy = Bad;
					delete m_DrawNoteMapList[Note];
					
					return 0;
				}
			}
		}
	}
	return 0;
}

bool BNoteMgr::Release()
{
	m_NoteMapList.clear();
	m_DrawNoteMapList.clear();
	return true;
}


BNoteMgr::BNoteMgr()
{
	m_NoteNum = 0;
}


BNoteMgr::~BNoteMgr()
{
}
