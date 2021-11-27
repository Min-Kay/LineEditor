#include "stdafx.h"
#include "Line.h"


CLine::CLine()
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
	MoveToEx(_DC, (int)m_tInfo.tLeftPos.fX, (int)m_tInfo.tLeftPos.fY, nullptr);
	LineTo(_DC, (int)m_tInfo.tRightPos.fX, (int)m_tInfo.tRightPos.fY);
}
