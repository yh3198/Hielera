#pragma once
#include "BNote.h"
#include "BCollision.h"

class BNoteMgr
{
public:
	static BNoteMgr& GetInstance()
	{
		static BNoteMgr singleton;
		return singleton;
	}
	bool CreateNote(TCHAR* pszLoad);
	bool CheckNote(float MusicPlaytime, bool ComboSpeedCheck);
	bool NoteSpeedContral(int Combo);
	int NoteCol(int KeyNum, int& NoteAccuracy, int& Combo, bool& ComboSpeedCheck);
	bool DrawNote(HDC hOffScreenDC, int& Combo, int& NoteAccuracy, bool& ComboSpeedCheck, int& MissCheck);
	bool Release();
	bool AllClearNote(int& Combo, int& GamePoint);

public:
	int m_NoteNum;
	list<BNote*> m_NoteMapList;
	vector<BNote*> m_DrawNoteMapList;

public:
	BNoteMgr();
	~BNoteMgr();
};

#define I_NoteMgr BNoteMgr::GetInstance()