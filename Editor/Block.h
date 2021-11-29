#pragma once
#include "Struct.h"
#include <Include.h>

class CBlock
{
public:
	CBlock();
	CBlock(BLOCKINFO _info);
	~CBlock();
public:
	void	Initialize();
	void	Update();
	void	Render(HDC _hdc);

	void	Update_Rect();
public:
	const	BLOCKINFO& Get_Info() const { return blockInfo; }
	void	Set_Info(POINT _pos, BLOCK::ID _id) { blockInfo.pos = _pos; blockInfo.id = _id; }
	const	RECT& Get_Rect() const { return rect; }
private:  
	INFO		info;
	BLOCKINFO blockInfo;
	RECT	  rect;
	HBRUSH    hbrush = NULL;
	HGDIOBJ		ori = NULL;
};

