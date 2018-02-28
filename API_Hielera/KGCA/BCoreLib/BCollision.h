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
	// 한점이 영역안에 있는가 ?
	bool RectInPt(RECT rt, POINT pt);

	// A영역이 B영역과 교차하느냐 ?
	bool RectInRect(RECT rt, RECT rt2);

	// A원이 B원과 교차하느냐 ?
	bool SphereInSphere(RECT rt, RECT rt2);

	// 한점이 A원 안에 있느냐 ?
	bool SphereInPt(RECT rt, BPOINT pt);

	int BCrashsize(RECT rt, RECT rt2);

public:
	BCollision();
	~BCollision();
};

#define I_Collision BCollision::GetInstance()