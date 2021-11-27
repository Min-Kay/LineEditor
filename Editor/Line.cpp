#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{
}

CLine::CLine(LINEINFO& _info)
	:m_tInfo(_info)
{
}


CLine::CLine(LINEPOS& _tLeft, LINEPOS& _tRight)
	: m_tInfo(_tLeft, _tRight)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC _DC)
{
	float	scroll = CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(_DC, (int)m_tInfo.tLeftPos.fX + scroll, (int)m_tInfo.tLeftPos.fY, nullptr);
	LineTo(_DC, (int)m_tInfo.tRightPos.fX + scroll, (int)m_tInfo.tRightPos.fY);
}
