#include "stdafx.h"
#include "MainApp.h"


CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release();
}

void CMainApp::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CKeyMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();
}

void CMainApp::Update(void)
{
	CLineMgr::Get_Instance()->Update();
}

void CMainApp::Late_Update(void)
{

}

void CMainApp::Render(void)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	CLineMgr::Get_Instance()->Render(m_DC);
}

void CMainApp::Release(void)
{
	ReleaseDC(g_hWnd, m_DC);

	CKeyMgr::Get_Instance()->Destroy_Intance();
	CLineMgr::Get_Instance()->Destroy_Intance();
}
