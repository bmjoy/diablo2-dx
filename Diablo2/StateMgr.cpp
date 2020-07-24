#include "StdAfx.h"
#include "StateMgr.h"

#include "Logo.h"
#include "Stage.h"
#include "Act2.h"

CStateMgr::CStateMgr(void)
: m_pState(NULL)
{
	SetProto();
}

CStateMgr::~CStateMgr(void)
{
	Release();
}


HRESULT CStateMgr::SetState(STATEID ID)
{
	map<STATEID, CStateObj*>::iterator	iter = m_mapState.find(ID);

	if(iter == m_mapState.end())
	{
		ERRORCHK(L"원형객체가 생성되지않았습니다.");
		return E_FAIL;
	}

	SAFE_DELETE(m_pState);

	m_pState = iter->second->Clone();
	m_pState->Initialize();
	return S_OK;
}

void CStateMgr::SetProto(void)
{
	if(!m_mapState.empty())
		return;

	int		iData0 = 10;
	int		iData1 = 20;

	//원형객체 생성 (state)
	m_mapState.insert(make_pair(STATEID_LOGO, new CLogo(iData0, iData1)));
	m_mapState.insert(make_pair(STATEID_ACT1, new CStage()));
	m_mapState.insert(make_pair(STATEID_ACT2, new CAct2()));
}

void CStateMgr::Progress(void)
{
	m_pState->Progress();
}
void CStateMgr::Render(void)
{
	m_pState->Render();
}

void CStateMgr::Release(void)
{
	for(map<STATEID, CStateObj*>::iterator iter = m_mapState.begin(); iter != m_mapState.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapState.clear();

	SAFE_DELETE(m_pState);
	
}

