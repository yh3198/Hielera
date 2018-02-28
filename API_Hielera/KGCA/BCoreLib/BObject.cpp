#include "BObject.h"

bool BObject::movePosition(float posX, float posY)
{
	pos.x = posX;
	col_rt.left = posX;
	pos.y = posY;
	col_rt.top = posY;
	return true;
}

bool BObject::NpcMove()
{
	if (pos.x  < 0)
	{
		pos.x = 1;
		m_DirectionX *= -1;
	}
	if (pos.x + rtSrc.right > 1280)
	{
		pos.x = 1279 - rtSrc.right;
		m_DirectionX *= -1;
	}
	if (pos.y < 0)
	{
		pos.y = 1;
		m_DirectionY *= -1;
	}
	if (pos.y + rtSrc.bottom > 720)
	{
		pos.y = 719 - rtSrc.bottom;
		m_DirectionY *= -1;
	}
	m_fSpeed = 400.0f * g_fSecPerFrame;
	pos.x += m_DirectionX*m_fSpeed;
	col_rt.left = pos.x;
	pos.y += m_DirectionY*m_fSpeed;
	col_rt.top = pos.y;
	return true;
}

BObject::BObject()
{
	m_fSpeed = 0;
	m_DirectionX = 1;
	m_DirectionY = 1;
}


BObject::~BObject()
{
}
