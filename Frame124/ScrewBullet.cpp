#include "stdafx.h"
#include "ScrewBullet.h"


CScrewBullet::CScrewBullet()
	: m_fCenterSpeed(0.f), m_fRevolutionAngle(0.f), m_bStart(true)
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));
}


CScrewBullet::~CScrewBullet()
{
	Release();
}

void CScrewBullet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 50.f;
	m_fCenterSpeed = 5.f;
	m_fDistance = 40.f;
	m_fRevolutionAngle = 0.f;
}

int CScrewBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_bStart)
	{
		m_tCenterPos.x = m_tInfo.fX;
		m_tCenterPos.y = m_tInfo.fY;
		m_fRevolutionAngle = m_fAngle;
		m_bStart = false;
	}


	m_tCenterPos.x += m_fCenterSpeed * cosf(m_fRevolutionAngle * PI / 180.f);
	m_tCenterPos.y -= m_fCenterSpeed * sinf(m_fRevolutionAngle * PI / 180.f);
	
	m_tInfo.fX = m_tCenterPos.x + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY = m_tCenterPos.y - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	m_fAngle += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update(void)
{
	/*if (100 >= m_tRect.left ||
		WINCX - 100 <= m_tRect.right ||
		100 >= m_tRect.top ||
		WINCY - 100 <= m_tRect.bottom)
	{
		m_bDead = true;
	}*/
}

void CScrewBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release(void)
{
	
}
