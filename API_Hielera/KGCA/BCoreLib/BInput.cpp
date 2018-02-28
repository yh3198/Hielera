#include "BInput.h"

DWORD BInput::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	if (sKey & 0x08000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE)
			m_dwKeyState[dwKey] = KEY_PUSH;
		else
			m_dwKeyState[dwKey] = KEY_HOLD;
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH || m_dwKeyState[dwKey] == KEY_HOLD)
			m_dwKeyState[dwKey] = KEY_UP;
		else
			m_dwKeyState[dwKey] = KEY_FREE;
	}
	return m_dwKeyState[dwKey];
}

void BInput::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_MOUSEWHEEL:
		{
			m_sMouseWheeldelta+=HIWORD(wParam);
			float fZ = m_sMouseWheeldelta / 120.0f;
		}break;
		case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			if (m_bDrag)
			{
				m_MovePt.x = x - m_DownPt.x;
				m_MovePt.y = y - m_DownPt.y;
			}
		}break;
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_dwMouseState[0] = KEY_PUSH;
			m_bDrag = true;
			m_DownPt.x = x;
			m_DownPt.y = y;
		}break;
		case WM_LBUTTONUP:
		{
			m_dwMouseState[0] = KEY_UP;
			m_bDrag = false;
		}break;
		case WM_MBUTTONDOWN:
		{
			m_dwMouseState[1] = KEY_PUSH;
		}break;
		case WM_MBUTTONUP:
		{
			m_dwMouseState[1] = KEY_UP;
		}break;
		case WM_RBUTTONDOWN:
		{
			m_dwMouseState[2] = KEY_PUSH;
		}break;
		case WM_RBUTTONUP:
		{
			m_dwMouseState[2] = KEY_UP;
		}break;
	}
}



bool BInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);
	
	GetCursorPos(&m_MousePos); // 마우스의 포지션을 받는 함수, 화면 좌표계 : 클라이언트 좌표계
	ScreenToClient(g_hWnd,&m_MousePos);
	return true;
}


bool BInput::Frame()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);

	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
		{
			if (m_dwMouseState[iButton] == KEY_PUSH)
			{
				m_dwMouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP)
		{
			if (m_dwMouseState[iButton] == KEY_UP)
			{
				m_dwMouseState[iButton] = KEY_FREE;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}
	return true;
}

bool BInput::Render()
{
	return true;
}

bool BInput::Release()
{
	return true;
}


BInput::BInput()
{
	m_bDrag = false;
}


BInput::~BInput()
{
}
