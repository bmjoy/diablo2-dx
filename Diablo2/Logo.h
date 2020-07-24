#pragma once

#include "Defines.h"
#include "StateObj.h"

class CLogo
	: public CStateObj
{
public:
	virtual void Initialize(void) ;
	virtual void Progress(void) ;
	virtual void Render(void) ;
	virtual void Release(void) ;
	virtual CStateObj* Clone(void) ;
public:
	CLogo(void);
	CLogo(int iData0, int iData1);
	~CLogo(void);
};
