#pragma once
#include "Defines.h"

class CMouseMgr
{
public:
	static inline POINT GetMousePos(void)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd,&pt);
		return pt;
	}
public:
	CMouseMgr(void);
	virtual ~CMouseMgr(void);
};
