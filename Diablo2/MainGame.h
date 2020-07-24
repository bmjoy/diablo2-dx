#pragma once

#include "Defines.h"

class CDevice;
class CStateMgr;
class CMainGame
{
private:
	CDevice*		m_pDevice;
	CStateMgr*		m_pStateMgr;

private: //fps
	int				m_iCnt;
	float			m_fData;
	TCHAR			m_szFps[127];
public:
	HRESULT Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);
public:
	CMainGame(void);
	~CMainGame(void);
};
