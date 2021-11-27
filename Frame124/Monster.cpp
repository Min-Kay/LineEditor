#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 2.f;
}

int CMonster::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	
	/*float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	float	fDistance = sqrtf(fX * fX + fY * fY);

	float	fRadian = acosf(fX / fDistance);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		fRadian = 2 * PI - fRadian;*/

	//m_fAngle = fRadian * 180.f / PI; // 라디안 값을 디그리 값으로 변환을 해봤다.
	//
	//if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	//	m_fAngle *= -1.f;

	//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	/*m_tInfo.fX += cosf(fRadian) * m_fSpeed;
	m_tInfo.fY -= sinf(fRadian) * m_fSpeed;*/

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	/*if ((100 >= m_tRect.left) || (WINCX - 100 <= m_tRect.right))
		m_fSpeed *= -1.f;*/
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	
}
