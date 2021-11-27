#pragma once

#include "Line.h"
#include "KeyMgr.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);


public:
	static	CLineMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr;

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
	void	KeyInput();
	void	Set_Pos();
	void	Reset_Pos();
	void	Drag();
	void	Drop();
	void	Drag_Erase();
	void	Set_Target();
	void    Erase_Target();
	void	Undo(); 
	void	Redo();
	void	Save();
	void	Load();

private:
	bool    Collision_Mouse();
	void	Update_RectPoint();

private:
	static CLineMgr*	m_pInstance;

	LINEPOS				m_tLinePos[2]; // 이을 점을 관리하는 점 리스트
	list<CLine*>		m_LineList; // 현재 사용중인 라인 리스트
	list<CLine*>		m_ReDoList; // 되돌리기용 라인 리스트
	list<CLine*>		m_DragList; // 드래그용 라인 리스트

	CLine*				m_TargetLine;
	INFO				m_MouseInfo;
	RECT				m_MouseRect;
	bool				m_MouseOn;

	LINEPOS				m_DragInfo[2];
	RECT				m_DragRect;
	bool				isDraged;
	bool				m_DragOn;

	DWORD				m_DrawPressTime;
	DWORD				m_UndoPressTime;
	DWORD				m_RedoPressTime;


};

