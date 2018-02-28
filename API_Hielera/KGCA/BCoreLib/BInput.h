#pragma once
#include "BStd.h"
/*������ ��ư�ٿ� ������ �� ��� ����ȭ�� �����*/
 // push�� up�� ������ �ѹ����� �߻�
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
	DWORD m_dwKeyState[256]; // ������ �迭�� ������ Ű�� �ش��ϴ� �ε���
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;  // POINT�� x�� y���� ���� ����ü // ���콺�� ��ġ��

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