#pragma once
#include "BSpriteMgr.h"

class BNote
{
public:
	int LineNum;
	int NoteType;
	float NoteHeight;
	float NoteSpeed;
	float Notetime; // ��Ʈ�� ������ �ð�
	RECT rt;
	RECT rtRsc;
	BPOINT Position;
	BPOINT CenterPosition;

public:
	BNote();
	~BNote();
};

