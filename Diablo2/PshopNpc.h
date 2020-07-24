#pragma once
#include "obj.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Defines.h"
#include "TimeMgr.h"
#include "Player.h"

class CPshopNpc :
	public CObj
{
private:
	float		m_fFrame; //프램
	int			m_iStateID; //npc 상태
	int			m_iMaxCnt; //npc max 프램
	
	D3DXMATRIX	m_TransShop; //변환행렬
	D3DXMATRIX	m_WorldShop; //월드행렬

	NEWRECT rcQUIT;

public:
	void SwitchSwap(bool* bSwitch);
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CPshopNpc(void);
	virtual ~CPshopNpc(void);
};
