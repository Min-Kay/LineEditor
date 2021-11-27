#pragma once

#include "Obj.h"
#include "Enum.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Bullet(list<CObj*>*  _pBullet);
	void		Set_Shield(list<CObj*>*  _pShield);

private:
	void		Key_Input(void);
	CObj*		Create_Shield(void);
	void		Jumping(void);
	
private:
	list<CObj*>*			m_pBullet = nullptr;
	list<CObj*>*			m_pShield = nullptr;
	POINT					m_tGun;
	
	bool					m_bJump;
	float					m_fJumpY;
	float					m_fJumpPower;
	float					m_fTime;


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

