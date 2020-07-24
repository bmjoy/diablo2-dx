#pragma once

#include "Defines.h"

class CObjMgr;
class CObj
{
protected:
	INFO			m_Info;
	STATUS		m_Status; //���� : �÷��̾�,�� ����
	NEWRECT		m_AtkRect; //���ݹ���
	NEWRECT		m_ObjRect; //������Ʈ�� ��Ʈ
	static	bool	m_bNotWalk; //��ȭâ�̳� �κ� �������� ������
	float			m_fDealTime; //�� ������ �ð�
	
protected:
	CObjMgr*	m_pObjMgr;
	float			m_fTime;
	bool			m_bSwitch;
public:
	//Get
	const INFO& GetInfo(void) const {return m_Info;}
	const STATUS& GetStat(void) const {return m_Status;}
	RECT GetAtkRect(void);
	RECT GetObjRect(void);
	RECT GetClickRect(NEWRECT rc);
	float  GetDealTime(void) { return m_fDealTime; }

	//Set
	void SetAngle(float _fAngle) { m_Status.fAngle = _fAngle; }
	void SetHp(int _iDamage) { m_Status.iHp -= _iDamage; }
	void SetMana(int _iUseMana) { m_Status.iMana -= _iUseMana; }
	void SetSwitch(bool _bSwitch) {	m_bSwitch	= 	_bSwitch;	}
	void ResetDealTime(void) { m_fDealTime = 0.f; }
	void SetRegenPos(float fX, float fY) {m_Info.vPos.x = fX; m_Info.vPos.y = fY; m_Info.vPos.z = 0;} //������ ��ġ
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(void)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;
	virtual CObj* Clone(void)PURE;
public:
	CObj(void);
	CObj(const INFO& Info);
	virtual ~CObj(void);
};
