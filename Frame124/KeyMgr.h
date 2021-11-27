#pragma once

#include "Include.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool		Key_Pressing(int _Key);
	bool		Key_Down(int _Key);
	bool		Key_Up(int _Key);

public:
	static	CKeyMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyMgr;

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
	static CKeyMgr*	m_pInstance;
	bool			m_bKeyState[VK_MAX];
};

