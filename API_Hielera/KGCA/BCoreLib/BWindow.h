#pragma once
#include "BStd.h"


class BWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	LPTSTR		strTiTleName;
	RECT		m_rtWindow;
	RECT		m_rtClient;


private:
	bool	SetRegister();
	bool	CreateWin(LPTSTR strTitleName, int iX, int iY, int iW, int iH);
	
public:
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool	SetWindow(HINSTANCE hInstance, int nCmdShow, LPTSTR strTitleName, int iX, int iY, int iW, int iH);

public:
	BWindow();
	virtual ~BWindow();
};

