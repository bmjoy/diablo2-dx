#pragma once

#include "Defines.h"
#include "obj.h"

class CLogoPlayer :
	public CObj
{
private:
	float		m_fAngle;
	float		m_fTime;
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CLogoPlayer(void);
	CLogoPlayer(const INFO& Info);
	~CLogoPlayer(void);
};
