#pragma once
#include "interface.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Defines.h"
#include "TimeMgr.h"
#include "TextMgr.h"

class CPanel :
	public CInterface
{
private:
	//HP,MP바
	D3DXMATRIX	m_matTransHp;
	D3DXMATRIX	m_matWorldHp;
	D3DXMATRIX	m_matTransMp;
	D3DXMATRIX	m_matWorldMp;

	STATUS		m_PlayerStat;

	RECT				m_HpRect;  //hp나 mp바를 원본 이미지로부터 얼마만큼만 읽어들일지 rect로 지정
	RECT				m_MpRect;

	NEWRECT			m_ShowHpRc;
	NEWRECT			m_ShowMpRc;
	
	float					m_ImgSizeY; // 비율로 구하는대 고정된 값이 필요
	float					m_HpSizeX; //위에 RECT에 들어갈 HP,MP 이미지의 실제 사이즈
	float					m_HpSizeY; //피가 위에서 아래로 내려가니깐 Y축만 바뀐다
	float					m_MpSizeX;
	float					m_MpSizeY;

	float					m_fHp;
	float					m_fMana;
	float					m_fMaxHp;
	float					m_fMaxMana;

	//중앙에 있는 미니바 (스텟,퀘스트,인벤,스킬)
	NEWRECT		rcStat;
	NEWRECT		rcQuest;
	NEWRECT		rcInven;
	NEWRECT		rcSkill;

public:	
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);

public:
	CPanel(void);
	~CPanel(void);
};
