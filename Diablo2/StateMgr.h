#pragma once

#include "Defines.h"
#include "SingleTon.h"
#include "StateObj.h"

class CStateMgr
	: public CSingleTon<CStateMgr>
{
private:
	map<STATEID, CStateObj*>			m_mapState;
	CStateObj*							m_pState;
public:
	void Progress(void);
	void Render(void);
	void Release(void);

public:
	void SetProto(void);
	HRESULT SetState(STATEID ID);

	friend CStateMgr* CSingleTon<CStateMgr>::GetInstance();
private:
	CStateMgr(void);
public:
	~CStateMgr(void);
};
