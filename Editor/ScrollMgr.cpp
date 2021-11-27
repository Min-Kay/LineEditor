#include "stdafx.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
	Release();
}

void CScrollMgr::Update(void)
{
	KeyInput();
}

void CScrollMgr::Late_Update(void)
{
}

void CScrollMgr::Release(void)
{

}

void CScrollMgr::KeyInput()
{
	Set_ScrollX(g_Wheel);
	g_Wheel = 0.f;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		Set_ScrollX(5.0f);
	}
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		Set_ScrollX(-5.0f);
	}
}
