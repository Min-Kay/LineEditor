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

	GetCursorPos(&pt);	// ���콺 Ŀ�� ��ġ ��ǥ�� ���ͼ� ����ü �ڷ����� ���� ä����

	ScreenToClient(g_hWnd, &pt);
	// ��ü ��ũ�� �������� Ŭ���̾�Ʈ(�츮�� ���� ������ â)��ǥ�� ��ȯ���ִ� �Լ�
	// 1���� : ���� ��ȯ�ϰ����ϴ� â�� �ڵ�
	// 2���� : ��ȯ�ϰ����ϴ� ���콺 ����ü �ּҰ�

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();
	ShowCursor(FALSE);
	// ���콺 Ŀ���� �׸��� ���� �����ϴ� �Լ�

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
