#include "StdAfx.h"
#include "StateObj.h"

#include "ObjMgr.h"

CStateObj::CStateObj(void)
: m_pObjProto(NULL)
, m_pObjMgr(CObjMgr::GetInstance())
{
}

CStateObj::CStateObj(int iData0, int iData1)
: m_iData0(iData0)
, m_iData1(iData1)
, m_pObjProto(NULL)
, m_pObjMgr(CObjMgr::GetInstance())
{

}

CStateObj::~CStateObj(void)
{
}
