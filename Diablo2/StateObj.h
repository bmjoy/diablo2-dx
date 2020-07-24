#pragma once

#include "Defines.h"
#include "ObjProto.h"

class CObjMgr;
class CStateObj
{
private: // юс╫ц
	int			m_iData0;
	int			m_iData1;
protected:
	CObjProto*		m_pObjProto;
	CObjMgr*		m_pObjMgr;
public:
	virtual void Initialize(void) PURE;
	virtual void Progress(void) PURE;
	virtual void Render(void) PURE;
	virtual void Release(void) PURE;
	virtual CStateObj* Clone(void) PURE;
public:
	CStateObj(void);
	CStateObj(int iData0, int iData1);
	virtual ~CStateObj(void);
};
