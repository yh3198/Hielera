#include "Sample.h"


bool Sample::Init()
{
	NowScene = Lobby;
	return true;
}

bool Sample::Frame()
{
	NowScene = BpScene.GetScene(NowScene)->Frame();
	return true;
}

bool Sample::Render()
{
	BpScene.GetScene(NowScene)->Render(m_hOffScreenDC);
	return true;
}

bool Sample::Release()
{
	return true;
}

void Sample::GetScene()
{

}


Sample::Sample()
{
}


Sample::~Sample()
{
}

KGCA_LYH_START
KGCA_LYH_GAMERUN(HIELERA, 0, 0, 1000, 1000)
KGCA_LYH_END