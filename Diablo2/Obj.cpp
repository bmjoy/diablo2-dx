#include "StdAfx.h"
#include "Obj.h"

#include "ObjMgr.h"

bool	CObj::m_bNotWalk;

CObj::CObj(void)
: m_pObjMgr(CObjMgr::GetInstance())
{
}

CObj::CObj(const INFO& Info)
: m_pObjMgr(CObjMgr::GetInstance())
, m_Info(Info)
{

}

RECT CObj::GetAtkRect(void)
{
	RECT rc = {
		long( m_AtkRect.fX - m_AtkRect.fSizeX/2 ),
		long( m_AtkRect.fY - m_AtkRect.fSizeY/2 ),
		long( m_AtkRect.fX + m_AtkRect.fSizeX/2 ),
		long( m_AtkRect.fY + m_AtkRect.fSizeY/2 ),
	};
	return rc;
}
RECT CObj::GetObjRect(void)
{
	RECT rc = {
		long( m_ObjRect.fX - ((m_ObjRect.fSizeX+20)/2) ),
		long( m_ObjRect.fY - ((m_ObjRect.fSizeY+70)/2) ),
		long( m_ObjRect.fX + ((m_ObjRect.fSizeX+20)/2) ),
		long( m_ObjRect.fY + ((m_ObjRect.fSizeY+70)/2 )),
	};
	return rc;
}

RECT CObj::GetClickRect(NEWRECT nrc)
{
	RECT rc = {
		long( nrc.fX - nrc.fSizeX/2 ),
		long( nrc.fY - nrc.fSizeY/2 ),
		long( nrc.fX + nrc.fSizeX/2 ),
		long( nrc.fY + nrc.fSizeY/2 ),
	};
	return rc;
}

CObj::~CObj(void)
{
}
