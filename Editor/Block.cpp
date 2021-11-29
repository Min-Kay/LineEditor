#include "stdafx.h"
#include "Block.h"
#include "ScrollMgr.h"

CBlock::CBlock()
{
}

CBlock::CBlock(BLOCKINFO _info)
{
	blockInfo = _info;

	info.fX = _info.pos.x;
	info.fY = _info.pos.y;
	Initialize();
	Update_Rect();
}

CBlock::~CBlock()
{
}

void CBlock::Initialize()
{
	info.fCX = 32.f;
	info.fCY = 32.f;

	switch (blockInfo.id)
	{
	case BLOCK::DEFAULT:
		hbrush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	case BLOCK::ITEM:
		hbrush = CreateSolidBrush(RGB(0, 255, 0));
		break;
	case BLOCK::BREAKABLE:
		hbrush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case BLOCK::INVISIBLE:
		hbrush = CreateSolidBrush(RGB(0, 0, 255));
		break;
	}
}

void CBlock::Update()
{
}

void CBlock::Render(HDC _hdc)
{
	info.fX = blockInfo.pos.x;
	info.fY = blockInfo.pos.y;
	Update_Rect();
	float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	RECT rc{rect.left + ScrollX, rect.top, rect.right + ScrollX,  rect.bottom };
	Rectangle(_hdc,rect.left + ScrollX, rect.top, rect.right + ScrollX,  rect.bottom);
	FillRect(_hdc,&rc,hbrush);
}

void CBlock::Update_Rect()
{
	rect.left = info.fX - info.fCX * 0.5f;
	rect.right = info.fX + info.fCX * 0.5f;
	rect.top = info.fY - info.fCY * 0.5f;
	rect.bottom = info.fY + info.fCY * 0.5f;
}
