#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Set_Bullet(list<CObj*>* _pBullet)
{
	m_pBullet = _pBullet;
}


void CPlayer::Set_Shield(list<CObj*>* _pShield)
{
	m_pShield = _pShield;
}

void CPlayer::Key_Input(void)
{
	

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (!m_bJump)
		{
			m_fJumpY = m_tInfo.fY;
			m_bJump = true;
		}
	}


}

CObj* CPlayer::Create_Shield(void)
{
	CObj*		pShield = CAbstractFactory<CShield>::Create();
	dynamic_cast<CShield*>(pShield)->Set_Target(this);

	return pShield;
}

void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (true == m_bJump)
	{
		m_tInfo.fY = m_fJumpY - (m_fJumpPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.2f;

		if (bLineCol && fY < m_tInfo.fY + (m_tInfo.fCY * 0.5f))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);
		}

	}
	
	else if(bLineCol)
		m_tInfo.fY = fY - (m_tInfo.fCY * 0.5f);

}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 200.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	
	m_tGun.x = m_tInfo.fX;
	m_tGun.y = m_tInfo.fY;

	m_fDistance = 100.f;

	m_fSpeed = 5.f;

	m_fTime = 0.f;
	m_bJump = false;
	m_fJumpPower = 50.f;
	m_fJumpY = 0.f;
}

int CPlayer::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	Key_Input();
	Jumping();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX + (cosf(m_fAngle * PI / 180.f) * m_fDistance));
	m_tGun.y = long(m_tInfo.fY - (sinf(m_fAngle * PI / 180.f) * m_fDistance));
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{
	
}
