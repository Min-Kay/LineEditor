#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
}

int CMouse::Update(void)
{
	POINT	pt{};

	GetCursorPos(&pt);	// 마우스 커서 위치 좌표를 얻어와서 구조체 자료형의 값을 채워줌

	ScreenToClient(g_hWnd, &pt);
	// 전체 스크린 영역에서 클라이언트(우리가 만든 윈도우 창)좌표로 변환해주는 함수
	// 1인자 : 내가 변환하고자하는 창의 핸들
	// 2인자 : 변환하고자하는 마우스 구조체 주소값

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();
	ShowCursor(FALSE);
	// 마우스 커서를 그릴지 말지 결정하는 함수

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release(void)
{
	
}
