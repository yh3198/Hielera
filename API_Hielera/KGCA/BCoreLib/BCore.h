#pragma once
#include "BWindow.h"
#include "BInput.h"
#include "BTimer.h"
#include "BNoteMgr.h"
#include "BSound.h"

class BCore : public BWindow
{
private:
	virtual bool BInit(int BWidth, int BHeight);
	virtual bool BFrame();
	virtual bool BRender(int BWidth, int BHeight);
	virtual bool BRelease();
	virtual bool BPreRender(int BWidth, int BHeight);
	virtual bool BPostRender(int BWidth, int BHeight);

public:
	HDC m_hScreenDC;
	HDC m_hOffScreenDC;
	HBRUSH m_hbrBack;
	HBITMAP m_hOldBrush;
	HBITMAP m_hOldBitmap;
	HBITMAP m_hOffScreenBitmap;

	BBitmap m_Bitmap;
	BBitmap m_Object;

	

	float HeroX;
	float HeroY;
	int SceneKey;

public:

	HFONT m_DefaultFont;

public:
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	bool Run(int BWidth,int BHeight);

public:
	BCore();
	virtual ~BCore();
};

