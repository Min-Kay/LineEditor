#include "stdafx.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CBlockMgr* CBlockMgr::pInstance = nullptr;

void CBlockMgr::Initialize()
{
}

void CBlockMgr::Update()
{
	KeyInput();
}

void CBlockMgr::Render(HDC _hdc)
{
	for (auto& i : block_list)
	{
		i->Render(_hdc);
	}
}

void CBlockMgr::Release()
{
	for_each(block_list.begin(), block_list.end(), CDeleteObj());
	for_each(Redo_list.begin(), Redo_list.end(), CDeleteObj());
	block_list.clear();
	Redo_list.clear();
	Drag_list.clear();
}

void CBlockMgr::Spawn_Block(BLOCK::ID _id)
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();

	CBlock* temp = new CBlock;
	temp->Set_Info(pt,_id);
	temp->Initialize();
	block_list.push_back(temp);
}

void CBlockMgr::Set_Drag(int num, float _x, float _y)
{
	m_DragInfo[num].fX = _x;
	m_DragInfo[num].fY = _y;
}

void CBlockMgr::KeyInput()
{

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UNDO_BLOCK))
	{
		Undo();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_REDO_BLOCK))
	{
		Redo();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SETTARGET_BLOCK))
	{
		Set_Target();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ERASETARGET_BLOCK))
	{
		Target_Erase();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ERASEDRAG_BLOCK))
	{
		Drag_Erase();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_DEFAULT_BLOCK))
	{
		Spawn_Block(BLOCK::DEFAULT);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ITEM_BLOCK))
	{
		Spawn_Block(BLOCK::ITEM);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_INVISIBLE_BLOCK))
	{
		Spawn_Block(BLOCK::INVISIBLE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_BREAKABLE_BLOCK))
	{
		Spawn_Block(BLOCK::BREAKABLE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SAVE_BLOCK))
	{
		Save();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LOAD_BLOCK))
	{
		Load();
	}
}

void CBlockMgr::Undo()
{
	if (block_list.empty())
		return;

	CBlock* temp = block_list.back();
	if (Redo_list.size() > 20)
	{
		Safe_Delete(Redo_list.front());
		Redo_list.pop_front();
	}
	block_list.pop_back();
	Redo_list.push_back(temp);
}

void CBlockMgr::Redo()
{
	if (Redo_list.empty())
		return;

	CBlock* temp = Redo_list.back();
	Redo_list.pop_back();
	block_list.push_back(temp);
}

void CBlockMgr::Drag()
{
	if (block_list.empty() || !m_DragInfo)
		return;

	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (!isDragged && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		m_DragInfo[0].fX = pt.x;
		m_DragInfo[0].fY = pt.y;
		isDragged = true;
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
	{
		m_DragInfo[1].fX = pt.x;
		m_DragInfo[1].fY = pt.y;
		Drop();
		isDragged = false;
	}

}

void CBlockMgr::Drop()
{
	if (block_list.empty())
		return;

	RECT rc{};

	m_DragRect.left = m_DragInfo[0].fX < m_DragInfo[1].fX ? m_DragInfo[0].fX : m_DragInfo[1].fX;
	m_DragRect.right = m_DragInfo[0].fX < m_DragInfo[1].fX ? m_DragInfo[1].fX : m_DragInfo[0].fX;
	m_DragRect.top = m_DragInfo[0].fY < m_DragInfo[1].fY ? m_DragInfo[0].fY : m_DragInfo[1].fY;
	m_DragRect.bottom = m_DragInfo[0].fY < m_DragInfo[1].fY ? m_DragInfo[1].fY : m_DragInfo[0].fY;

	list<CBlock*>::iterator iter = Drag_list.begin();
	for (; iter != Drag_list.end();)
	{
		iter = Drag_list.erase(iter);
	}

	for (auto& iter : block_list)
	{
		if (IntersectRect(&rc, &m_DragRect, &iter->Get_Rect()))
		{
			Drag_list.push_back(iter);
		}
	}
	m_DragOn = true;
}

void CBlockMgr::Drag_Erase()
{
	if (Drag_list.empty())
		return;
	
	list<CBlock*>::iterator j = Drag_list.begin();
	for (; j != Drag_list.end();)
	{
		list<CBlock*>::iterator i = block_list.begin();
		for (; i != block_list.end();)
		{
			if (*i == *j)
			{
				Redo_list.push_back(*i);
				i = block_list.erase(i);
				j = Drag_list.erase(j);
				break;
			}
			else
			{
				++i;
			}
		}
	}
	m_DragOn = false;
}

void CBlockMgr::Set_Target()
{
	if (block_list.empty())
		return;

	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (long)CScrollMgr::Get_Instance()->Get_ScrollX();

	for (auto& i : block_list)
	{
		if (PtInRect(&i->Get_Rect(), pt))
		{
			m_Target = i;
			return;
		}
	}
}

void CBlockMgr::Target_Erase()
{
	if (!m_Target || block_list.empty())
		return;

	list<CBlock*>::iterator iter = block_list.begin();
	for (; iter != block_list.end();)
	{
		if (*iter == m_Target)
		{
			block_list.erase(iter);
			Redo_list.push_back(m_Target);
			m_Target = nullptr;
			return;
		}
		else
			++iter;
	}
}

void CBlockMgr::Save()
{
	if (block_list.empty())
		return;

	HANDLE			hFile = CreateFile(BLOCK_SAVE, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : block_list)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(BLOCKINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OKCANCEL);
}

void CBlockMgr::Load()
{
	HANDLE			hFile = CreateFile(BLOCK_SAVE, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	BLOCKINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(BLOCKINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		block_list.push_back(new CBlock(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), _T("Success"), MB_OKCANCEL);
}

CBlockMgr::CBlockMgr()
{
}

CBlockMgr::~CBlockMgr()
{
	Release();
}
