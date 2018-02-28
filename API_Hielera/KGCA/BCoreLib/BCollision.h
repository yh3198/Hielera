#pragma once
#include "BStd.h"


class BCollision
{
public:
	static BCollision& GetInstance()
	{
		static BCollision singleton;
		return singleton;
	}

public:
	// ������ �����ȿ� �ִ°� ?
	bool RectInPt(RECT rt, POINT pt);

	// A������ B������ �����ϴ��� ?
	bool RectInRect(RECT rt, RECT rt2);

	// A���� B���� �����ϴ��� ?
	bool SphereInSphere(RECT rt, RECT rt2);

	// ������ A�� �ȿ� �ִ��� ?
	bool SphereInPt(RECT rt, BPOINT pt);

	int BCrashsize(RECT rt, RECT rt2);

public:
	BCollision();
	~BCollision();
};

#define I_Collision BCollision::GetInstance()