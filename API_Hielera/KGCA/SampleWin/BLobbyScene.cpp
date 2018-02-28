#include "BLobbyScene.h"

TCHAR g_ID[128] = { 0, };
TCHAR g_PW[128] = { 0, };
HWND m_IDWnd;
HWND m_PWWnd;

bool BLobbyScene::Init()
{
	return true;
}
DWORD BLobbyScene::Frame()
{
	I_SoundMgr.play(TitleBG);
	static float fVolume = 0.3f;
	I_SoundMgr.m_pChannel[TitleBG]->setVolume(fVolume);
	
	if(I_Collision.RectInPt(m_Yes, I_InputMgr.m_MousePos))
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (I_InputMgr.m_dwMouseState[0] == KEY_PUSH)
		{
			I_SoundMgr.stop(TitleBG);
			I_SoundMgr.play(MenuUp);
			I_NoteMgr.CreateNote(L"BNote.txt");
			Sleep(400);
			GetWindowText(m_IDWnd, g_ID, 128);
			GetWindowText(m_PWWnd, g_PW, 128);
			ShowWindow(m_IDWnd, 0);
			ShowWindow(m_PWWnd, 0);
			return Game;
		}
	}
	if (I_Collision.RectInPt(m_No, I_InputMgr.m_MousePos))
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (I_InputMgr.m_dwMouseState[0] == KEY_PUSH)
		{
			I_SoundMgr.play(MenuUp);
			Sleep(400);
			g_GameClose = true;
		}
	}
	return Lobby;
}
bool BLobbyScene::Render(HDC hOffScreenDC)
{
	I_ObjmapMgr.GetOBj(hOffScreenDC, 0); // Title
	I_ObjmapMgr.GetOBj(hOffScreenDC, 1); // yes
	if (I_Collision.RectInPt(m_Yes, I_InputMgr.m_MousePos))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, 2);
	}
	I_ObjmapMgr.GetOBj(hOffScreenDC, 3); // no
	if (I_Collision.RectInPt(m_No, I_InputMgr.m_MousePos))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, 4);
	}
	if (I_Collision.RectInPt(m_ID, I_InputMgr.m_MousePos))
	{
		SetCursor(LoadCursor(NULL, IDC_IBEAM));
		if (I_InputMgr.m_dwMouseState[0] == KEY_PUSH)
		{
			m_IDWnd = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 433, 702, 185, 23, g_hWnd, (HMENU)ID_EDIT_ID, NULL, NULL);
		}
	}
	if (I_Collision.RectInPt(m_PW, I_InputMgr.m_MousePos))
	{
		SetCursor(LoadCursor(NULL, IDC_IBEAM));
		if (I_InputMgr.m_dwMouseState[0] == KEY_PUSH)
		{
			m_PWWnd = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 433, 735, 185, 23, g_hWnd, (HMENU)ID_EDIT_PW, NULL, NULL);
		}
	}
	return true;
}
bool BLobbyScene::Release()
{
	return true;
}

BLobbyScene::BLobbyScene()
{
	m_Yes = { 391, 777, 103, 36 };
	m_No = { 511, 777, 103 ,36 };
	m_ID = { 433, 702, 185 , 23 };
	m_PW = { 433, 735, 185 , 23 };
}


BLobbyScene::~BLobbyScene()
{
}
