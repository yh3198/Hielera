#include "BWindow.h"

BWindow			*g_pWindow = NULL;
HWND			g_hWnd;       //extern �Լ��� ����� ������ �ߺ����ǰ� �Ǵ°� ���������� ������ ������ cpp�� �־���� �Ѵ�.
HINSTANCE		g_hInstance;

int g_Scene = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg)
	{
	case WM_DESTROY: // ������â �ݱ��
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
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
	// ������ Ŭ���� ���� ����ü
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
