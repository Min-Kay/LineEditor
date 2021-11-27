#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "GuideBullet.h"

CMainGame::CMainGame()
	: m_dwTime(0)
	, m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 256);
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	// player 추가
	
	//CObj*	pObj = nullptr;

	//pObj = CAbstractFactory<CGuideBullet>::Create();
	//CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);

	///*pObj = CAbstractFactory<CMonster>::Create(200.f, 200.f);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);*/
	//
	//pObj = CAbstractFactory<CMonster>::Create(500.f, 400.f);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	//pObj = CAbstractFactory<CMonster>::Create(600.f, 200.f);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);
	

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());

	CLineMgr::Get_Instance()->Initialize();

}

void CMainGame::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();	
}

void CMainGame::Render(void)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	CLineMgr::Get_Instance()->Render(m_DC);
	CObjMgr::Get_Instance()->Render(m_DC);

		

	// 문자열 출력함수(소수점 자리수는 출력이 불가능)
	//TCHAR	szBuff[32] = L"";
	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJID::BULLET].size()); // winapi 제공함수(모든 서식 문자을 지원하지 않음)
	//TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	// 문자열 출력함수(소수점 자리수는 출력 가능)
	TCHAR	szTemp[32] = L"";
	swprintf_s(szTemp, L"Bullet : %f", 3.14f);	// visual c++라이브러리에서 제공(모든 서식 문자를 지원)
	TextOut(m_DC, 150, 50, szTemp, lstrlen(szTemp));

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);
		m_dwTime = GetTickCount();
		m_iFPS = 0;
	}
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_DC);	

	CKeyMgr::Get_Instance()->Destroy_Intance();
	CLineMgr::Get_Instance()->Destroy_Intance();
	CObjMgr::Get_Instance()->Destroy_Intance();
	
}

