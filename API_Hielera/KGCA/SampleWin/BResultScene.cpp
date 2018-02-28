#include "BResultScene.h"

bool BResultScene::Init()
{
	return true;
}
DWORD BResultScene::Frame()
{
	if (I_InputMgr.m_dwMouseState[0] == KEY_PUSH)
	{
		I_SoundMgr.stop(ResultBG);
		Sleep(400);
		Release();
		return Lobby;
	}
	return Result;
}
bool BResultScene::Render(HDC hOffScreenDC)
{
	I_SoundMgr.play(ResultBG);
	SetTextColor(hOffScreenDC, RGB(255, 255, 255));

	I_ObjmapMgr.GetOBj(hOffScreenDC, 20);
	m_DefaultFont = CreateFont(30, 0, 0, FW_BOLD, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, 0, L"a¾Æ¶ì");
	HGDIOBJ Offobj = SelectObject(hOffScreenDC, m_DefaultFont);
	_stprintf_s(m_csBuffer, L"%s ´ÔÀÇ ÃÑÁ¡¼ö", g_ID);
	SetTextAlign(hOffScreenDC, TA_CENTER);
	TextOut(hOffScreenDC, 500, 440, m_csBuffer, wcslen(m_csBuffer));
	DeleteObject(Offobj);


	m_DefaultFont = CreateFont(80, 0, 0, FW_BOLD, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, 0, L"a¾Æ¶ì");
	HGDIOBJ SE_Offobj = SelectObject(hOffScreenDC, m_DefaultFont);
	_stprintf_s(m_csBuffer, L"%d", g_TotalScore);
	SetTextAlign(hOffScreenDC, TA_CENTER);
	TextOut(hOffScreenDC, 500, 500, m_csBuffer, wcslen(m_csBuffer));
	DeleteObject(SE_Offobj);

	SetTextAlign(hOffScreenDC, TA_LEFT);
	m_DefaultFont = CreateFont(20, 0, 0, FW_BOLD, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, 0, L"a¾Æ¶ì");
	HGDIOBJ RE_Offobj = SelectObject(hOffScreenDC, m_DefaultFont);
	SetTextColor(hOffScreenDC, RGB(0, 0, 0));

	return true;
}
bool BResultScene::Release()
{
	
	return true;
}


BResultScene::BResultScene()
{
}


BResultScene::~BResultScene()
{
}
