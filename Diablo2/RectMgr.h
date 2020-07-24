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
	void	Render(NEWRECT rc,int id); //캐릭터나 유닛 rect 보여주기

public:
	friend CRectMgr* CSingleTon<CRectMgr>::GetInstance();
public:
	CRectMgr(void);
	~CRectMgr(void);
};
