#include "stdafx.h"
#include "MainApp.h"
#include "ScrollMgr.h"
#include "BlockMgr.h"

CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release();
}

void CMainApp::Initialize(void)
{
	CScrollMgr::Get_Instance()->Initialize(); 
	CKeyMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();
	CBlockMgr::Get_Instance()->Initialize();

}

void CMainApp::Update(void)
{
	CScrollMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
}

void CMainApp::Late_Update(void)
{

}

void CMainApp::Render(void)
{
	Rectangle(g_hdc, 0, 0, WINCX, WINCY);

	CLineMgr::Get_Instance()->Render(g_hdc);
	CBlockMgr::Get_Instance()->Render(g_hdc);
}

void CMainApp::Release(void)
{
	CScrollMgr::Get_Instance()->Destroy_Intance(); 
	CKeyMgr::Get_Instance()->Destroy_Intance();
	CLineMgr::Get_Instance()->Destroy_Intance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
}
