#include "BWindow.h"

BWindow			*g_pWindow = NULL;
HWND			g_hWnd;       //extern 함수를 헤더에 넣으면 중복정의가 되는건 마찬가지기 때문에 무조건 cpp에 넣어줘야 한다.
HINSTANCE		g_hInstance;

int g_Scene = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg)
	{
	case WM_DESTROY: // 윈도우창 닫기시
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	default:
		break;
	}
	LRESULT HRet = g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT BWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

bool BWindow::SetRegister()
{
	WNDCLASSEX  wcex;
	// 윈도우 클래스 생성 구조체
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"KGCA_LYH";

	if (RegisterClassEx(&wcex) == false)
	{
		return false;
	}
	return true;
}

bool BWindow::CreateWin(LPTSTR strTiTleName, int iX, int iY, int iW, int iH)
{
	RECT rt = { 0,0, iW, iH };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindow (L"KGCA_LYH", strTiTleName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, iX, iY, rt.right-rt.left, rt.bottom-rt.top, NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL)
		return false;
	return true;
}

bool BWindow::SetWindow(HINSTANCE hInstance, int nCmdShow, LPTSTR strTitleName, int iX, int iY, int iW, int iH)
{
	g_hInstance = m_hInstance = hInstance;

	if (SetRegister() == NULL)
		return false;
	if (CreateWin(strTitleName, iX, iY, iW, iH) == NULL)
		return false;

	g_hWnd = m_hWnd;
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	return true;
}

BWindow::BWindow()
{
	g_pWindow = this;
}


BWindow::~BWindow()
{
}
