#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CBullet::Update(void)
{	
	if (true == m_bDead)
		return OBJ_DEAD;

	/*switch (m_eDir)
	{
	case BULLET::LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case BULLET::RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;

	case BULLET::UP:
		m_tInfo.fY -= m_fSpeed;

		break;

	case BULLET::DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	}*/

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;


	Update_Rect();

	return OBJ_NOEVENT;

}

void CBullet::Late_Update(void)
{
	if (100			>= m_tRect.left		||
		WINCX - 100 <= m_tRect.right	||
		100			>= m_tRect.top		||
		WINCY - 100 <= m_tRect.bottom)
	{ 
		m_bDead = true;
	}		
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
	
}
