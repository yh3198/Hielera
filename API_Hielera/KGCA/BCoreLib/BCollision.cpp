#include "BCollision.h"

// 한점이 영역안에 있는가 ?
bool BCollision::RectInPt(RECT rt, POINT pt)
{
	if (pt.x <= (rt.left+rt.right) && pt.x >= rt.left)
	{
		if (pt.y <= (rt.bottom+rt.top) && pt.y >= rt.top)
			return true;
	}
	return false;
}
int BCollision::BCrashsize(RECT rt, RECT rt2)
{
	int Crashsize = sqrt(((rt.top + rt.bottom) - rt2.top)*((rt.top + rt.bottom) - rt2.top)) / 9;
	Crashsize += 2;
	return Crashsize;
}

// A영역이 B영역과 교차하느냐 ?
bool BCollision::RectInRect(RECT rt, RECT rt2)
{
	int Total_width = rt2.right + rt.right - 16;
	int Total_height = rt2.bottom + rt.bottom + 16;
	


	if (rt2.left <= rt.left)
	{
		if (rt2.top >= rt.top)
			if (((rt.left+rt.right) - rt2.left) <= Total_width && ((rt2.top+rt2.bottom) - rt.top) <= Total_height)
			{
				return true;
			}
		if (rt2.top <= rt.top)
			if (((rt.left+rt.right) - rt2.left) <= Total_width && ((rt.top+rt.bottom) - rt2.top) <= Total_height)
			{
				return true;
			}
	}
	if (rt2.left >= rt.left)
	{
		if (rt2.top >= rt.top)
		{
			if (((rt2.left+rt2.right) - rt.left) <= Total_width && ((rt2.top+rt2.bottom) - rt.top) <= Total_height)
			{
				return true;
			}
		}
		if (rt2.top <= rt.top)
			if (((rt2.left+rt2.right) - rt.left) <= Total_width && ((rt.top+rt.bottom) - rt2.top) <= Total_height)
			{
				return true;
			}
	}
	return false;
}

// A원이 B원과 교차하느냐 ?
bool BCollision::SphereInSphere(RECT rt, RECT rt2)
{
	/*노트 충돌용*/
	rt.right += 20;
	rt.bottom += 20;

	double harp = sqrt((rt.right / 2)*(rt.right / 2) + (rt.bottom / 2)*(rt.bottom / 2));
	double harp2 = sqrt((rt2.right / 2)*(rt2.right / 2) + (rt2.bottom / 2)*(rt2.bottom / 2));
	double Totalharp = harp + harp2;
	BPOINT rtP;
	BPOINT rt2P;
	rtP.x = rt.left + rt.right / 2;
	rtP.y = rt.top + rt.bottom / 2;
	rt2P.x = rt2.left + rt2.right / 2;
	rt2P.y = rt2.top + rt2.bottom / 2;

	if (sqrt((rtP.x - rt2P.x)*(rtP.x - rt2P.x) + (rtP.y - rt2P.y)*(rtP.y - rt2P.y)) <= Totalharp)
	{
		return true;
	}
	return false;
}

// 한점이 A원 안에 있느냐 ?
bool BCollision::SphereInPt(RECT rt, BPOINT pt)
{
	double harp = sqrt((rt.right / 2)*(rt.right / 2) + (rt.bottom / 2)*(rt.bottom / 2));
	BPOINT rtP;
	rtP.x = rt.left + rt.right / 2;
	rtP.y = rt.top + rt.bottom / 2;
	if (sqrt((rtP.x - pt.x)*(rtP.x - pt.x) + (rtP.y - pt.y)*(rtP.y - pt.y)) <= harp)
	{
		return true;
	}
	return false;
}



BCollision::BCollision()
{
}


BCollision::~BCollision()
{
}
