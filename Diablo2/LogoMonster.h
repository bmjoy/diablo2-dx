#pragma once

#include "Defines.h"
#include "Obj.h"

class CLogoMonster
	: public CObj
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);

public:
	CLogoMonster(void);
	CLogoMonster(const INFO& Info);
	~CLogoMonster(void);
};
