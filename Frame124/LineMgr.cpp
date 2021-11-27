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
	for (auto& iter : m_LineList)
		iter->Render(_DC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	for_each(m_ReDoList.begin(), m_ReDoList.end(), CDeleteObj());
	m_LineList.clear();
	m_ReDoList.clear();
}

void CLineMgr::KeyInput()
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON)) // 선 새로 긋기
	{
		ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1)) // 마지막 선 지우기
	{
		if (m_LineList.empty())
			return;

		m_ReDoList.push_back(m_LineList.back());
		m_LineList.pop_back();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2)) // 마지막으로 지운 선 되돌리기
	{
		if (m_ReDoList.empty())
			return;

		m_LineList.push_back(m_ReDoList.back());
		m_ReDoList.pop_back();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F5)) // m_LineList 세이브
	{
		if (m_LineList.empty())
			return;

		Save();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F6)) // m_LineList 로드
	{
		Load();
	}
}

void CLineMgr::Save()
{
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

void CLineMgr::Load()
{
	FILE* saveFile = nullptr;
	errno_t saveData = fopen_s(&saveFile, LINE_SAVE, "rb");

	if (0 == saveData)
	{
		while (true)
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



bool CLineMgr::Collision_Line(const float& _fX, float* _fY)
{
	// 두 점을 지나는 직선의 방정식
	// Y  - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)

	// 플레이어의  Y 값을 구하도록 공식을 변경하자
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	if (m_LineList.empty())
		return false;

	for (auto& iter : m_LineList)
	{
		if (iter->Get_Info().tLeftPos.fX < _fX &&
			iter->Get_Info().tRightPos.fX > _fX)
		{
			float x1 = iter->Get_Info().tLeftPos.fX;
			float y1 = iter->Get_Info().tLeftPos.fY;

			float x2 = iter->Get_Info().tRightPos.fX;
			float y2 = iter->Get_Info().tRightPos.fY;

			*_fY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
			return true;
		}
	}

	return false;
}

