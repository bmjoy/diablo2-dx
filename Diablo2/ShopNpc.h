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

class CShopNpc :
	public CObj
{
private:
	float		m_fFrame; //����
	int			m_iStateID; //npc ����
	int			m_iMaxCnt; //npc max ����
	//bool		m_bSwitch; //���� �����ְ� �Ⱥ����ְ� ���� ��CObj�� ����

	D3DXMATRIX	m_TransShop; //��ȯ���
	D3DXMATRIX	m_WorldShop; //�������

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
	CShopNpc(void);
	virtual ~CShopNpc(void);
};
