#pragma once

#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "Shield.h"

#include "LineMgr.h"
#include "KeyMgr.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;	// dc 보관하기 위한 변수
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[256];
};

