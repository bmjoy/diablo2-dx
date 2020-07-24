#pragma once
#include "singleton.h"
#include "Defines.h"
#include "Device.h"

class CTextMgr :
	public CSingleTon<CTextMgr>
{
public:
	void MakeText(PTCHAR _pText, float _fX, float _fY, float _fScaleX = 1.f, float _fScaleY = 1.f)
	{
		RECT		rcFont = {0};
		D3DXMATRIX			matTrans;
		D3DXMATRIX			matWorld;
		D3DXMATRIX			matScale;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans,_fX,_fY,0.f);
		D3DXMatrixScaling(&matScale,_fScaleX,_fScaleY,0.f);
		matWorld = matScale * matTrans;
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);		
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), _pText, lstrlen(_pText), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
public:
	friend CTextMgr* CSingleTon<CTextMgr>::GetInstance();
public:
	CTextMgr(void);
	~CTextMgr(void);
};

/*
		//
		TCHAR		szInt[128];
		ZeroMemory(&szInt, sizeof(szInt));
		wsprintf(szInt, L"%d %d" ,int(m_vecTile[i]->iX),int(m_vecTile[i]->iY) );
		CTextMgr::GetInstance()->MakeText(szInt,m_vecTile[i]->iX,m_vecTile[i]->iY);
*/