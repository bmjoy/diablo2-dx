#pragma once

#include "Defines.h"
#include "StateObj.h"

class CStage
	: public CStateObj
{
public:
	virtual void Initialize(void) ;
	virtual void Progress(void) ;
	virtual void Render(void) ;
	virtual void Release(void) ;
	virtual CStateObj* Clone(void) ;
public:
	CStage(void);
	CStage(int iData0, int iData1);
	~CStage(void);
};
