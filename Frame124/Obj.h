#pragma once

#include "Define.h"
#include "Struct.h"
#include "Enum.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Pos(float _fX, float _fY);
	void			Set_Direction(BULLET::DIR _eDir);
	void			Set_Dead(void);
	void			Set_Angle(float _fAngle);
	void			Set_Target(CObj* _pTarget);
	void			Set_PosX(float _fX);
	void			Set_PosY(float _fY);


	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

	void				Update_Rect(void);

protected:
	RECT			m_tRect;
	INFO			m_tInfo;
	float			m_fSpeed;
	float			m_fAngle;
	float			m_fDistance;
	bool			m_bDead;	
	BULLET::DIR		m_eDir;
	CObj*			m_pTarget;

};

