#pragma once
#include "Block.h"
class CBlockMgr
{
public:
	void	Initialize();
	void	Update();
	void	Render(HDC _hdc);
	void	Release();

public:
	void	Spawn_Block(BLOCK::ID _id);

public:
	void	Set_Drag(int num, float _x, float _y);

public:
	void	KeyInput();
	void	Undo();
	void	Redo();
	void	Drag();
	void	Drop();
	void	Drag_Erase();
	void	Set_Target();
	void	Target_Erase();

public:
	void		Save();
	void		Load();
	
private:
	list<CBlock*> block_list;
	list<CBlock*> Redo_list;
	list<CBlock*> Drag_list;

	LINEPOS				m_DragInfo[2];
	RECT				m_DragRect;
	bool				isDragged;
	bool				m_DragOn;
	CBlock*				m_Target = nullptr;

private :
	CBlockMgr() ;
	~CBlockMgr() ;

public:
	static CBlockMgr* Get_Instance() {
		if (!pInstance)
			pInstance = new CBlockMgr; 
		return pInstance;
	}

	static void	Destroy_Instance()
	{
		if (pInstance)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}

private:
	static CBlockMgr* pInstance;
};

