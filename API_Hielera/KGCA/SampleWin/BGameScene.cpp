#include "BGameScene.h"

int g_TotalScore = 0;

int BGameScene::NoteAccuracyCheck(int Gamepoint)
{
	if (GamePoint > 6)
		return Perfect;
	if (GamePoint >= 3 && GamePoint <= 6)
		return Great;
	if (GamePoint == 1 || GamePoint == 2)
		return Good;
	return Good;
}

bool BGameScene::GamePointdraw(int GamePoint)
{
	return true;
}

bool BGameScene::Init()
{
	return true;
}
DWORD BGameScene::Frame()
{
	if (BPlayTime > 114 || MissCheck > 10)
	{
		I_SoundMgr.stop(GameBG);
		g_TotalScore = TotalGamePoint;
		Release();
		return Result;
	}
	BPlayTime += g_fSecPerFrame; // ³ëÆ®À½¾Ç ½Ã°£ Ã¼Å©
	if (Combo == 100 && ComboSpeedCheck == false)
	{
		ComboSpeedCheck = I_NoteMgr.NoteSpeedContral(Combo);
	}
	I_NoteMgr.CheckNote(BPlayTime, ComboSpeedCheck);
	return Game;
}
bool BGameScene::Render(HDC hOffScreenDC)
{
	static float fVolume = 0.3f;
	I_SoundMgr.m_pChannel[GameBG]->setVolume(fVolume);
	if ( BPlayTime > 5 && BPlayTime < 6)
	{
		I_SoundMgr.play(GameBG);
	}
	I_ObjmapMgr.GetOBj(hOffScreenDC, 27); // BG_back
	I_ObjmapMgr.GetOBj(hOffScreenDC, 5); // GameBG
	for (int Bomb = 0; Bomb < BombCount; Bomb++)
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (6+Bomb));
	}
	I_ObjmapMgr.GetOBj(hOffScreenDC, 9); // CdCover
	for (int NBotton = 0; NBotton < NBottonCount; NBotton++)
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (10 + NBotton));
	}
	
	
	if (I_InputMgr.KeyCheck('D')==KEY_PUSH)
	{
		GamePoint = I_NoteMgr.NoteCol(1, NoteAccuracy, Combo, ComboSpeedCheck) * 10;
		if (GamePoint != 0 && SpPlaying_1 == true)
		{
			map<int, BSprite*>::iterator itor;
			itor = I_SpmapMgr.m_SpMapList.find(0);
			(*itor).second->Reset();
		}
		if (GamePoint != 0)
		{
			SpPlaying_1 = true;
			NoteAccuracy = NoteAccuracyCheck(GamePoint);
		}
		GamePointdraw(GamePoint);
	}
	if (I_InputMgr.KeyCheck('D'))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (15));
	}
	TotalGamePoint += GamePoint;
	GamePoint = 0;
	


	if (I_InputMgr.KeyCheck('F') == KEY_PUSH)
	{
		GamePoint = I_NoteMgr.NoteCol(2, NoteAccuracy, Combo, ComboSpeedCheck) * 10;
		if (GamePoint != 0 && SpPlaying_2 == true)
		{
			map<int, BSprite*>::iterator itor;
			itor = I_SpmapMgr.m_SpMapList.find(1);
			(*itor).second->Reset();
		}
		if (GamePoint != 0)
		{
			SpPlaying_2 = true;
			NoteAccuracy = NoteAccuracyCheck(GamePoint);
		}
		GamePointdraw(GamePoint);
	}
	if (I_InputMgr.KeyCheck('F'))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (16));
	}
	TotalGamePoint += GamePoint;
	GamePoint = 0;




	if (I_InputMgr.KeyCheck(VK_SPACE) == KEY_PUSH)
	{
		GamePoint = I_NoteMgr.NoteCol(3, NoteAccuracy, Combo, ComboSpeedCheck) * 10;
		if (GamePoint != 0 && SpPlaying_3 == true)
		{
			map<int, BSprite*>::iterator itor;
			itor = I_SpmapMgr.m_SpMapList.find(2);
			(*itor).second->Reset();
		}
		if (GamePoint != 0)
		{
			SpPlaying_3 = true;
			NoteAccuracy = NoteAccuracyCheck(GamePoint);
		}
		GamePointdraw(GamePoint);
	}
	if (I_InputMgr.KeyCheck(VK_SPACE))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (17));
	}
	TotalGamePoint += GamePoint;
	GamePoint = 0;


	if (I_InputMgr.KeyCheck('J') == KEY_PUSH)
	{
		GamePoint = I_NoteMgr.NoteCol(4, NoteAccuracy, Combo, ComboSpeedCheck) * 10;
		if (GamePoint != 0 && SpPlaying_4 == true)
		{
			map<int, BSprite*>::iterator itor;
			itor = I_SpmapMgr.m_SpMapList.find(3);
			(*itor).second->Reset();
		}
		if (GamePoint != 0)
		{
			SpPlaying_4 = true;
			NoteAccuracy = NoteAccuracyCheck(GamePoint);
		}
		GamePointdraw(GamePoint);
	}
	if (I_InputMgr.KeyCheck('J'))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (18));
	}
	TotalGamePoint += GamePoint;
	GamePoint = 0;


	if (I_InputMgr.KeyCheck('K') == KEY_PUSH)
	{
		GamePoint = I_NoteMgr.NoteCol(5, NoteAccuracy, Combo, ComboSpeedCheck) * 10;
		if (GamePoint != 0 && SpPlaying_5 == true)
		{
			map<int, BSprite*>::iterator itor;
			itor = I_SpmapMgr.m_SpMapList.find(4);
			(*itor).second->Reset();
		}
		if (GamePoint != 0)
		{
			SpPlaying_5 = true;
			NoteAccuracy = NoteAccuracyCheck(GamePoint);
		}
		GamePointdraw(GamePoint);
	}
	if (I_InputMgr.KeyCheck('K'))
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, (19));
	}

	if (I_InputMgr.KeyCheck('Q') == KEY_PUSH && BombCount != 0) // ÆøÅº
	{
		ComboSpeedCheck = I_NoteMgr.AllClearNote(Combo , GamePoint);
		SpPlaying_6 = true;
		BombCount--;
	}

	TotalGamePoint += GamePoint;
	GamePoint = 0;
	
	_stprintf_s(m_csBuffer, L"Point = %d", TotalGamePoint);
	TextOut(hOffScreenDC, 768, 80, m_csBuffer, wcslen(m_csBuffer));


	if (SpPlaying_1 == true)
		I_SpmapMgr.GetSp(hOffScreenDC, 0, I_SpmapMgr.GetSpPtr(0)->pos, SpPlaying_1);
	if (SpPlaying_2 == true)
		I_SpmapMgr.GetSp(hOffScreenDC, 1, I_SpmapMgr.GetSpPtr(1)->pos, SpPlaying_2);
	if (SpPlaying_3 == true)
		I_SpmapMgr.GetSp(hOffScreenDC, 2, I_SpmapMgr.GetSpPtr(2)->pos, SpPlaying_3);
	if (SpPlaying_4 == true)
		I_SpmapMgr.GetSp(hOffScreenDC, 3, I_SpmapMgr.GetSpPtr(3)->pos, SpPlaying_4);
	if (SpPlaying_5 == true)
		I_SpmapMgr.GetSp(hOffScreenDC, 4, I_SpmapMgr.GetSpPtr(4)->pos, SpPlaying_5);
	if (SpPlaying_6 == true)
		I_SpmapMgr.GetSp(hOffScreenDC, 11, I_SpmapMgr.GetSpPtr(11)->pos, SpPlaying_6);

 	I_NoteMgr.DrawNote(hOffScreenDC, Combo, NoteAccuracy, ComboSpeedCheck, MissCheck);
	I_SpmapMgr.GetCombo(hOffScreenDC, Combo);
	if (NoteAccuracy != 0)
	{
		I_ObjmapMgr.GetOBj(hOffScreenDC, NoteAccuracy);
	}

	return true;
}
bool BGameScene::Release()
{
	I_NoteMgr.Release();
	TotalGamePoint = 0;
	BPlayTime = 0;
	BombCount = 3;
	NBottonCount = 5;
	MissCheck = 0;
	GamePoint = 0;
	TotalGamePoint = 0;
	Combo = 0;
	NoteAccuracy = 0;
	ComboSpeedCheck = false;
	return true;
}

BGameScene::BGameScene()
{
	BPlayTime = 0;
	MissCheck = 0;
	GamePoint = 0;
	TotalGamePoint = 0;
	Combo = 0;
	NoteAccuracy = 0;
	ComboSpeedCheck = false;
	SpPlaying_1 = false;
	SpPlaying_2 = false;
	SpPlaying_3 = false;
	SpPlaying_4 = false;
	SpPlaying_5 = false;
	SpPlaying_6 = false;
	BombCount = 3;
	NBottonCount = 5;
}


BGameScene::~BGameScene()
{
}
