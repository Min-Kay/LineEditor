#include "stdafx.h"
#include "LineMgr.h"

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
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		Set_Pos();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON)) 
	{
		Reset_Pos();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		Set_Target(); 
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F4))
	{
		Undo_Target();
	}

	if (CKeyMgr::Get_Instance()->Key_Rollover(VK_F1, VK_F2)) 
	{
		Load();
	}

	if (CKeyMgr::Get_Instance()->Key_Double_Click(VK_F6)) 
	{
		Save();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1)) 
	{
		Undo();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2)) 
	{
		Redo();
	}

}

void CLineMgr::Set_Pos() // 선 긋기
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

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

	FILE* saveFile = nullptr;
	errno_t saveData = fopen_s(&saveFile, LINE_SAVE, "wb");

	if (0 == saveData)
	{
		auto& iter = m_LineList.begin();
		for (; iter != m_LineList.end();)
		{
			fwrite(*iter, sizeof(CLine), 1, saveFile);
			++iter;
		}	
		fclose(saveFile);
	}
}

void CLineMgr::Load() // m_LineList 로드
{
	FILE* saveFile = nullptr;
	errno_t saveData = fopen_s(&saveFile, LINE_SAVE, "rb");

	if (0 == saveData)
	{
		while(true)
		{
			CLine* temp = new CLine;
			int iCnt = fread(&(*temp), sizeof(CLine), 1, saveFile);

			if (1 > iCnt)
			{
				Safe_Delete(temp);
				break;
			}

			m_LineList.push_back(&(*temp));
		}

		fclose(saveFile);
	}

}


bool CLineMgr::Collision_Mouse()
{
	if (m_LineList.empty())
		return false;

	for (auto& iter : m_LineList)
	{
		//x축 좌표 기준 충돌
		if (iter->Get_Info().tLeftPos.fX <= iter->Get_Info().tRightPos.fX)
		{
			if (iter->Get_Info().tLeftPos.fX < m_MouseInfo.fX &&
				iter->Get_Info().tRightPos.fX > m_MouseInfo.fX)
			{
				float x1 = iter->Get_Info().tLeftPos.fX;
				float y1 = iter->Get_Info().tLeftPos.fY;

				float x2 = iter->Get_Info().tRightPos.fX;
				float y2 = iter->Get_Info().tRightPos.fY;

				float result = ((y2 - y1) / (x2 - x1)) * (m_MouseInfo.fX - x1) + y1;

				if (result > m_MouseRect.top && result < m_MouseRect.bottom)
				{
					m_TargetLine = iter;
					return true;
				}
				else
				{
					m_TargetLine = nullptr;
				}
			}
		}
		else if (iter->Get_Info().tLeftPos.fX > iter->Get_Info().tRightPos.fX)
		{
			if (iter->Get_Info().tLeftPos.fX > m_MouseInfo.fX &&
				iter->Get_Info().tRightPos.fX < m_MouseInfo.fX)
			{
				float x1 = iter->Get_Info().tRightPos.fX;
				float y1 = iter->Get_Info().tRightPos.fY;

				float x2 = iter->Get_Info().tLeftPos.fX;
				float y2 = iter->Get_Info().tLeftPos.fY;

				float result = ((y2 - y1) / (x2 - x1)) * (m_MouseInfo.fX - x1) + y1;

				if (result > m_MouseRect.top && result < m_MouseRect.bottom)
				{
					m_TargetLine = iter;
					return true;
				}
				else
				{
					m_TargetLine = nullptr;
				}
			}
		}
		
		// y축 좌표 기준 충돌 
		if (iter->Get_Info().tLeftPos.fY <= iter->Get_Info().tRightPos.fY)
		{
			if (iter->Get_Info().tLeftPos.fY < m_MouseInfo.fY &&
				iter->Get_Info().tRightPos.fY > m_MouseInfo.fY)
			{
				float x1 = iter->Get_Info().tLeftPos.fX;
				float y1 = iter->Get_Info().tLeftPos.fY;

				float x2 = iter->Get_Info().tRightPos.fX;
				float y2 = iter->Get_Info().tRightPos.fY;

				float result = (m_MouseInfo.fY - y1) / ((y2 - y1) / (x2 - x1)) + x1; 

				if (result > m_MouseRect.left && result < m_MouseRect.right)
				{
					m_TargetLine = iter;
					return true;
				}
				else
				{
					m_TargetLine = nullptr;
				}
			}
		}
		else if (iter->Get_Info().tLeftPos.fY > iter->Get_Info().tRightPos.fY)
		{
			if (iter->Get_Info().tLeftPos.fY > m_MouseInfo.fY &&
				iter->Get_Info().tRightPos.fY < m_MouseInfo.fY)
			{
				float x1 = iter->Get_Info().tRightPos.fX;
				float y1 = iter->Get_Info().tRightPos.fY;

				float x2 = iter->Get_Info().tLeftPos.fX;
				float y2 = iter->Get_Info().tLeftPos.fY;

				float result = (m_MouseInfo.fY - y1) / ((y2 - y1) / (x2 - x1)) + x1;

				if (result > m_MouseRect.left && result < m_MouseRect.right)
				{
					m_TargetLine = iter;
					return true;
				}
				else
				{
					m_TargetLine = nullptr;
				}
			}
		}
	}

	return false;
}

void CLineMgr::Update_RectPoint() // 마우스 RECT 출력용
{
	m_MouseRect.left = long(m_MouseInfo.fX - m_MouseInfo.fCX * 0.5f);
	m_MouseRect.right = long(m_MouseInfo.fX + m_MouseInfo.fCX * 0.5f);
	m_MouseRect.top = long(m_MouseInfo.fY - m_MouseInfo.fCY * 0.5f);
	m_MouseRect.bottom = long(m_MouseInfo.fY + m_MouseInfo.fCY * 0.5f);
}


