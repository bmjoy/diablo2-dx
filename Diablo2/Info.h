#pragma once
#include "interface.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Defines.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

class CInfo :
	public CInterface
{
private:
	STATUS		m_PlayerStat;

public:
	void MakeText(PTCHAR _pText, float _fX, float _fY);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);

public:
	CInfo(void);
	~CInfo(void);
};

