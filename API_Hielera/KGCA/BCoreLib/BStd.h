#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <vector>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <math.h>
#include <list>
#include <deque>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "winmm.lib") 
#pragma comment(lib, "BCoreLib.lib") 

using namespace std;
using namespace FMOD;


extern int g_TotalScore;
extern int g_Scene;
extern bool g_GameClose;
extern HWND		 g_hWnd;  //extern 재확인할것
extern HINSTANCE g_hInstance;
extern float g_fSecPerFrame;
extern HWND m_IDWnd;
extern HWND m_PWWnd;
extern TCHAR g_ID[128];
extern TCHAR g_PW[128];

#define KGCA_LYH_START int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR IpCmdLine, int nCmdShow) {
#define KGCA_LYH_GAMERUN(S,X,Y,W,H) Sample gSample; if (!gSample.SetWindow(hInstance, nCmdShow, L#S, X, Y, W, H)) {MessageBox(0, _T("CreateWindow 초기화실패"), _T("Fatal error"), MB_OK);	return 0; } ShowCursor(TRUE); gSample.Run(W, H);
#define KGCA_LYH_END return 1;}

#define ID_EDIT_ID 100
#define ID_EDIT_PW 101

struct BPOINT
{
	float  x;
	float  y;
};

enum KeyState {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};

enum SoundTrack {
	TitleBG = 0,
	MenuUp,
	MenuSelect,
	GameBG,
	CloseBG,
	ResultBG,
};

enum SceneState {
	LobbyScene = 0,
	GameScene,
	ResultScene,
};

enum NoteClearPoint {
	Perfect = 22,
	Great,
	Good,
	Bad,
	Miss,
};