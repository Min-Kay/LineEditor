#include "stdafx.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	m_TargetLine = nullptr;
	m_MouseInfo.fCX = 20;
	m_MouseInfo.fCY = 20;
	m_DrawPressTime = 0.f;
	m_UndoPressTime = 0.f;
	m_RedoPressTime = 0.f;
}

void CLineMgr::Update(void)
{
	KeyInput();
	
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC _DC)
{

#ifdef _DEBUG
	Rectangle(_DC,m_MouseRect.left,m_MouseRect.top,m_MouseRect.right,m_MouseRect.bottom);
#endif

	for (auto& iter : m_LineList)
		iter->Render(_DC);

}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	for_each(m_ReDoList.begin(),m_ReDoList.end(),CDeleteObj());
	m_LineList.clear();
	m_ReDoList.clear(); 
}

void CLineMgr::KeyInput()
{
	
	if (m_DrawPressTime + 50.f < GetTickCount() && CKeyMgr::Get_Instance()->Key_Pressing(VK_DRAW))
	{
		Set_Pos();
		m_DrawPressTime = GetTickCount();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_DRAW))
	{
		Set_Pos();
	}

	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RESETPOS)) 
	{
		Reset_Pos();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SETTARGET))
	{
		Set_Target(); 
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UNDOTARGET))
	{
		Undo_Target();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SAVE))
	{
		Save();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LOAD))
	{
		Load();
	}

	if (m_UndoPressTime + 300.f < GetTickCount() && CKeyMgr::Get_Instance()->Key_Pressing(VK_UNDO))
	{
		Undo();
		m_UndoPressTime = GetTickCount();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_UNDO)) 
	{
		Undo();
	}


	if (m_RedoPressTime + 300.f < GetTickCount() && CKeyMgr::Get_Instance()->Key_Pressing(VK_REDO))
	{
		Redo();
		m_RedoPressTime = GetTickCount();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_REDO)) 
	{
		Redo();
	}

	

}

void CLineMgr::Set_Pos() // 선 긋기
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_tLinePos[0].fX == (float)pt.x && m_tLinePos[0].fY == (float)pt.y)
		return; 


	if (!m_tLinePos[0].fX && !m_tLinePos[0].fY)
	{
		m_tLinePos[0].fX = (float)pt.x;
		m_tLinePos[0].fY = (float)pt.y;
	}
	else
	{
		m_tLinePos[1].fX = (float)pt.x;
		m_tLinePos[1].fY = (float)pt.y;

		m_LineList.push_back(new CLine(m_tLinePos[0], m_tLinePos[1]));

		m_tLinePos[0].fX = m_tLinePos[1].fX;
		m_tLinePos[0].fY = m_tLinePos[1].fY;
	}

}

void CLineMgr::Reset_Pos() // 선 새로 긋기
{
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
}

void CLineMgr::Set_Target()
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();

	m_MouseInfo.fX = pt.x;
	m_MouseInfo.fY = pt.y;
	Update_RectPoint();

	Collision_Mouse();
}

void CLineMgr::Undo_Target()
{
	if (!m_TargetLine || m_LineList.empty())
		return;

	auto& iter = m_LineList.begin();
	for (; iter != m_LineList.end();)
	{
		if (*iter == m_TargetLine)
		{
			m_ReDoList.push_back(m_TargetLine);
			iter = m_LineList.erase(iter);
			m_TargetLine = nullptr; 
		}
		else
		{
			++iter;
		}
	}
}

void CLineMgr::Undo() // 마지막 선 지우기
{
	if (m_LineList.empty())
		return;

	if (m_ReDoList.size() >= 20)
	{
		Safe_Delete(m_ReDoList.front());
		m_ReDoList.pop_front();
	}

	m_ReDoList.push_back(m_LineList.back());
	m_LineList.pop_back();
}


void CLineMgr::Redo() // 마지막으로 지운 선 되돌리기
{
	if (m_ReDoList.empty())
		return;

	m_LineList.push_back(m_ReDoList.back());
	m_ReDoList.pop_back();
}

void CLineMgr::Save() // m_LineList 세이브
{
	if (m_LineList.empty())
		return;

	HANDLE			hFile = CreateFile(LINE_SAVE, GENERIC_WRITE,NULL,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);					

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINEINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OKCANCEL);
}

void CLineMgr::Load() // m_LineList 로드
{
	HANDLE			hFile = CreateFile(LINE_SAVE,GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);					

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), _T("Success"), MB_OKCANCEL);

}


bool CLineMgr::Collision_Mouse()
{
	if (m_LineList.empty())
		return false;

	for (auto& iter : m_LineList)
	{
		float x1 = iter->Get_Info().tLeftPos.fX;
		float y1 = iter->Get_Info().tLeftPos.fY;

		float x2 = iter->Get_Info().tRightPos.fX;
		float y2 = iter->Get_Info().tRightPos.fY;

		//x축 좌표 기준 충돌
		if (x1 <= x2)
		{
			if (x1 < m_MouseInfo.fX && x2 > m_MouseInfo.fX)
			{

				float result = ((y2 - y1) / (x2 - x1)) * (m_MouseInfo.fX - x1) + y1;

				if (result > m_MouseRect.top && result < m_MouseRect.bottom)
				{
					m_TargetLine = iter;
					return true;
				}
			}
		}
		
		if (x1 > x2)
		{
			if (x1 > m_MouseInfo.fX && x2 < m_MouseInfo.fX)
			{

				float result = ((y2 - y1) / (x2 - x1)) * (m_MouseInfo.fX - x1) + y1;

				if (result > m_MouseRect.top && result < m_MouseRect.bottom)
				{
					m_TargetLine = iter;
					return true;
				}
			}
		}
		
		// y축 좌표 기준 충돌 
		if (y1 <= y2)
		{
			if (y1 < m_MouseInfo.fY &&y2 > m_MouseInfo.fY)
			{
				float result = (m_MouseInfo.fY - y1) / ((y2 - y1) / (x2 - x1)) + x1; 

				if (result > m_MouseRect.left && result < m_MouseRect.right)
				{
					m_TargetLine = iter;
					return true;
				}
			}
		}
		
		if (y1 > y2)
		{
			if (y1 > m_MouseInfo.fY && y2 < m_MouseInfo.fY)
			{
				float result = (m_MouseInfo.fY - y1) / ((y2 - y1) / (x2 - x1)) + x1;

				if (result > m_MouseRect.left && result < m_MouseRect.right)
				{
					m_TargetLine = iter;
					return true;
				}
			}
		}
	}

	return false;
}

void CLineMgr::Update_RectPoint() // 마우스 RECT 출력용
{
	float px = (long)CScrollMgr::Get_Instance()->Get_ScrollX();
	m_MouseRect.left = long(m_MouseInfo.fX - m_MouseInfo.fCX * 0.5f) + px;
	m_MouseRect.right = long(m_MouseInfo.fX + m_MouseInfo.fCX * 0.5f) + px;
	m_MouseRect.top = long(m_MouseInfo.fY - m_MouseInfo.fCY * 0.5f);
	m_MouseRect.bottom = long(m_MouseInfo.fY + m_MouseInfo.fCY * 0.5f);
}


