#pragma once
#include "Stateobj.h"
#include "Defines.h"

class CAct2 :
	public CStateObj
{
public:
	virtual void Initialize(void) ;
	virtual void Progress(void) ;
	virtual void Render(void) ;
	virtual void Release(void) ;
	virtual CStateObj* Clone(void) ;
public:
	CAct2(void);
	~CAct2(void);
};
