#pragma once

#include "Include.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void		Initialize(void) {}
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC) {}
	void		Release(void);

public:
	float			Get_ScrollX() { return m_fScroll; }
	void			Set_ScrollX(float _fX) { m_fScroll += _fX; }

public:
	void			KeyInput();

public:
	static	CScrollMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static	void		Destroy_Intance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*	m_pInstance;
	float				m_fScroll = 0.f;
};

