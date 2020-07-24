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
	//HP,MP��
	D3DXMATRIX	m_matTransHp;
	D3DXMATRIX	m_matWorldHp;
	D3DXMATRIX	m_matTransMp;
	D3DXMATRIX	m_matWorldMp;

	STATUS		m_PlayerStat;

	RECT				m_HpRect;  //hp�� mp�ٸ� ���� �̹����κ��� �󸶸�ŭ�� �о������ rect�� ����
	RECT				m_MpRect;

	NEWRECT			m_ShowHpRc;
	NEWRECT			m_ShowMpRc;
	
	float					m_ImgSizeY; // ������ ���ϴ´� ������ ���� �ʿ�
	float					m_HpSizeX; //���� RECT�� �� HP,MP �̹����� ���� ������
	float					m_HpSizeY; //�ǰ� ������ �Ʒ��� �������ϱ� Y�ุ �ٲ��
	float					m_MpSizeX;
	float					m_MpSizeY;

	float					m_fHp;
	float					m_fMana;
	float					m_fMaxHp;
	float					m_fMaxMana;

	//�߾ӿ� �ִ� �̴Ϲ� (����,����Ʈ,�κ�,��ų)
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
