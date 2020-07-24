#pragma once
#include "SingleTon.h"
#include "Defines.h"

class CRectMgr :
	public CSingleTon<CRectMgr>
{
private:
	D3DXMATRIX			m_matTranslation;
	D3DXMATRIX			m_matWorld;
	D3DXVECTOR3			m_vecCenter;
public:
	void	Initialize(void);
	void	Release(void);
	void	Render(NEWRECT rc,int id); //ĳ���ͳ� ���� rect �����ֱ�

public:
	friend CRectMgr* CSingleTon<CRectMgr>::GetInstance();
public:
	CRectMgr(void);
	~CRectMgr(void);
};
