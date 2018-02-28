#pragma once
#include "BSpriteMgr.h"

class BNote
{
public:
	int LineNum;
	int NoteType;
	float NoteHeight;
	float NoteSpeed;
	float Notetime; // 노트가 등장할 시간
	RECT rt;
	RECT rtRsc;
	BPOINT Position;
	BPOINT CenterPosition;

public:
	BNote();
	~BNote();
};

