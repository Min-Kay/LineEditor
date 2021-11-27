#pragma once

#include "Define.h"
#include "Enum.h"
#include "Struct.h"
#include "CollisionMgr.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Target(OBJID::ID _eID, CObj* pObj);

public:
	void		Add_Object(OBJID::ID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC m_DC);
	void		Release(void);

private:
	list<CObj*>		m_ObjList[OBJID::END];

public:
	static	CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
				m_pInstance = new CObjMgr;
		
		return m_pInstance;
	}

	static	void		Destroy_Intance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*			m_pInstance;

};

