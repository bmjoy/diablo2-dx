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
#include "StateMgr.h"

class CWayPoint :
	public CObj
{
private:
	float		m_fFrame; //����
	int			m_iStateID; //npc ����
	int			m_iMaxCnt; //npc max ����

	D3DXMATRIX	m_TransShop; //��ȯ���
	D3DXMATRIX	m_WorldShop; //�������

	NEWRECT rcQUIT;
	NEWRECT rcACT1;
	NEWRECT rcACT2;
	NEWRECT rcACT3;

	bool GoAct1;
	bool GoAct2;
	bool GoAct3;

public:
	void SwitchSwap(bool* bSwitch);
	//stage.cpp���� state �ٲٱ� ���Ѱ�..
	bool SwitchAct1(void) { return GoAct1; }
	bool SwitchAct2(void) { return GoAct2; }
	bool SwitchAct3(void) { return GoAct3; }

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CWayPoint(void);
	virtual ~CWayPoint(void);
};
