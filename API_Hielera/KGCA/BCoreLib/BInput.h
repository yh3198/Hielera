#pragma once
#include "BStd.h"
/*윈도우 버튼다운 업으로 할 경우 동기화가 힘들다*/
 // push와 up은 무조건 한번씩만 발생
class BInput
{
public:
	static BInput& GetInstance()
	{
		static BInput singleton;
		return singleton;
	}
public:
	bool  m_bDrag;
	POINT m_DownPt;
	POINT m_MovePt;
	short m_sMouseWheeldelta;
	DWORD m_dwKeyState[256]; // 각각의 배열이 각각의 키에 해당하는 인덱스
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;  // POINT는 x값 y값을 가진 구조체 // 마우스의 위치값

public:
	DWORD KeyCheck(DWORD dwKey);
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	BInput();
	~BInput();
};

#define I_InputMgr BInput::GetInstance()