#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"

CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();
}

void CGuideBullet::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 3.f;
}

int CGuideBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::MONSTER, this);

	if (nullptr != m_pTarget)
	{
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDistance = sqrtf(fX * fX + fY * fY);

		float	fRadian = acosf(fX / fDistance);

		m_fAngle = fRadian * 180.f / PI; 

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}

	m_tInfo.fX += (m_fSpeed * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY -= (m_fSpeed * sinf(m_fAngle * PI / 180.f));

	Update_Rect();

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update(void)
{
	/*if (100 >= m_tRect.left ||
		WINCX - 100 <= m_tRect.right ||
		100 >= m_tRect.top ||
		WINCY - 100 <= m_tRect.bottom)
	{
		m_bDead = true;
	}*/
}

void CGuideBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CGuideBullet::Release(void)
{
	
}
