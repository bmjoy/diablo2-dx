#include "StdAfx.h"
#include "Info.h"
#include "SoundMgr.h"

CInfo::CInfo(void)
{
}

CInfo::~CInfo(void)
{
}

void CInfo::Initialize(void)
{
	//ÁÂÇ¥°ü·Ã
	m_Info.vPos.x = 0;
	m_Info.vPos.y =0;
	m_Info.vPos.z = 0;

	m_Info.vCenter = D3DXVECTOR3(0.f,0.f,0.f);
	D3DXMatrixTranslation(&m_Info.matTrans,m_Info.vPos.x ,m_Info.vPos.y,m_Info.vPos.z);
	m_Info.matWorld = m_Info.matTrans;
	
	//Ã¢¶ç¿ì±â 
	m_fTime = 0;
	m_bSwitch = false;

}

void CInfo::Progress(void)
{
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PUSH_KEY(KEY_C) && m_fTime > 0.3f)
	{
		CSoundMgr::GetInstance()->SoundPlay(2,0);
		m_fTime = 0;
		//À¯Àú °ÈÁö¸¶
		m_bNotWalk = SwitchSwap(m_bNotWalk);
		//½ºÅÝÃ¢ ÄÑ°í ²ô°í
		m_bSwitch = SwitchSwap(m_bSwitch);
	}
}

void CInfo::Render(void)
{
	/////
	if( m_bSwitch )
	{
		m_PlayerStat = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->GetStat(); //½ºÅÝ¾ò¾î¿È

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_INFO, OBJECT_STATEID_INTERFACE_STATUS)
			, NULL, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		//Èû½ºÅÝ
		TCHAR		szStr[128];
		ZeroMemory(&szStr, sizeof(szStr));
		wsprintf(szStr, L"%d", m_PlayerStat.Str);
		MakeText(szStr,158,150);
		//Áö´É
		TCHAR		szInt[128];
		ZeroMemory(&szInt, sizeof(szInt));
		wsprintf(szInt, L"%d", m_PlayerStat.Int);
		MakeText(szInt,158,211);
		//¹ÎÃ¸
		TCHAR		szDex[128];
		ZeroMemory(&szDex, sizeof(szDex));
		wsprintf(szDex, L"%d", m_PlayerStat.Dex);
		MakeText(szDex,158,298);
		//»ý¸í·Â
		TCHAR		szVit[128];
		ZeroMemory(&szVit, sizeof(szVit));
		wsprintf(szVit, L"%d", m_PlayerStat.Vit);
		MakeText(szVit,158,360);
		//°ø°Ý·Â
		TCHAR		szAtk[128];
		ZeroMemory(&szAtk, sizeof(szAtk));
		wsprintf(szAtk, L"%d", m_PlayerStat.iAtk);
		MakeText(szAtk,341,149);
		//¹æ¾î·Â
		TCHAR		szDef[128];
		ZeroMemory(&szDef, sizeof(szDef));
		wsprintf(szDef, L"%d", m_PlayerStat.iDef);
		MakeText(szDef,341,173);
		//LV
		TCHAR		szLv[128];
		ZeroMemory(&szLv, sizeof(szLv));
		wsprintf(szLv, L"%d", m_PlayerStat.Lv);
		MakeText(szLv,152,107);
	}
}

void CInfo::MakeText(PTCHAR _pText, float _fX, float _fY)
{
		RECT		rcFont = {0};
		D3DXMATRIX			matTrans;
		D3DXMATRIX			matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans,_fX,_fY,0);
		matWorld = matTrans;
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);		
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), _pText, lstrlen(_pText), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CInfo::Release(void)
{

}

CObj* CInfo::Clone( void )
{
	return new CInfo(*this);
}
