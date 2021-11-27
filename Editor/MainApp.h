#pragma once

#include "Include.h"
#include "MainApp.h"

#include "KeyMgr.h"
#include "LineMgr.h"

class CMainApp
{
public:
	CMainApp();
	~CMainApp();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;	// dc �����ϱ� ���� ����
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[256];
};

