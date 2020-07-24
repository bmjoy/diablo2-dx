#pragma once
#include "Defines.h"
#include "singleton.h"

class CKeyMgr :
	public CSingleTon<CKeyMgr>
{
private:
	// ������ ���� Ű�� ������ ������ ����.
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
