#pragma once

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src);
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);

private:
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);
	static bool Check_Rect(CObj* pDest, CObj* pSrc, float* _pWidth, float* _pHeight);

};

