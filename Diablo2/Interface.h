#pragma once
#include "obj.h"
#include "Defines.h"

class CInterface :
	public CObj
{
protected:
	float		m_fTime;
	//bool		m_bSwitch;
public:
	bool SwitchSwap(bool bSwitch);
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
	virtual CObj* Clone(void)PURE;
public:
	CInterface(void);
	virtual ~CInterface(void);
};
