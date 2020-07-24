#pragma once
#include "Defines.h"
#include "singleton.h"

class CKeyMgr :
	public CSingleTon<CKeyMgr>
{
private:
	// 유저가 누른 키의 정보를 저장할 변수.
	DWORD			m_dwKey;
public:
	void SetKeyCheck(void);
	bool PushKey(DWORD dwKey);
	
	friend CKeyMgr* CSingleTon<CKeyMgr>::GetInstance(void);
private:
	CKeyMgr(void);
public:
	~CKeyMgr(void);
};
