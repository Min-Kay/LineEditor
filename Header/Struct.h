#pragma once
#include "Enum.h"

typedef struct tagInfo
{
	float		fX;	// ���� �׸����� �ϴ� ��ü�� ���� x
	float		fY; // ���� �׸����� �ϴ� ��ü�� ���� y
	float		fCX; // ���� ������
	float		fCY; // ���� ������

}INFO;


typedef	struct	tagLinePos	 
{
	float		fX;
	float		fY;

	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float _X, float _Y)
		: fX(_X), fY(_Y)
	{

	}

}LINEPOS;

typedef struct tagLineInfo
{
	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeft, LINEPOS& _tRight)
		: tLeftPos(_tLeft), tRightPos(_tRight)
	{	}
}LINEINFO;

typedef struct tagBlockInfo
{
	POINT	pos;
	BLOCK::ID id;

	tagBlockInfo() { ZeroMemory(this, sizeof(tagBlockInfo)); }
	tagBlockInfo(POINT& _pos, BLOCK::ID& _id)
		: pos(_pos), id(_id)
	{	}

}BLOCKINFO;

class CDeleteObj
{
public:
	CDeleteObj() {}
	~CDeleteObj() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}


