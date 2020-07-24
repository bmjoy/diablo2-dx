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
#include "TextMgr.h"
#include "QuestMgr.h"

class CSonic :
	public CObj
{
private:
	float		m_fFrame; //프램
	int			m_iStateID; //npc 상태
	int			m_iMaxCnt; //npc max 프램

	//대화창
	D3DXMATRIX	m_TransShop; //변환행렬
	D3DXMATRIX	m_WorldShop; //월드행렬
	//소닉 마을로 이동
	D3DXMATRIX	m_TransTown; //변환행렬
	D3DXMATRIX	m_WorldTown; //월드행렬
	D3DXVECTOR3	m_vTownPos; //소닉 마을에 있을때 좌표

	NEWRECT		rcTalk;

	bool talk1;
	bool talk2;
	bool talkend;

public:
	void	SwitchSwap(bool* bSwitch);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CSonic(void);
	virtual ~CSonic(void);
};
