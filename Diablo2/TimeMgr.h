#pragma once

#include "Defines.h"
#include "SingleTon.h"

class CTimeMgr
	: public CSingleTon<CTimeMgr>
{
private:
	LARGE_INTEGER			m_CpuTick;
	LARGE_INTEGER			m_InvaliTime;
	LARGE_INTEGER			m_FixTime;
	LARGE_INTEGER			m_LastTime;
	float					m_fTime;
public:
	float	GetPixelPerSec(void) {return m_fTime;}

public:
	void SetPixelPerSec(void);
	
	friend CTimeMgr* CSingleTon<CTimeMgr>::GetInstance();
private:
	CTimeMgr(void);
public:
	~CTimeMgr(void);
};
