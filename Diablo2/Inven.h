#pragma once
#include "interface.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Defines.h"
#include "TimeMgr.h"

class CInven :
	public CInterface
{
private:
		STATUS		m_PlayerStat;
public:

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);

public:
	CInven(void);
	~CInven(void);
};
