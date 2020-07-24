#include "StdAfx.h"
#include "Inven.h"
#include "SoundMgr.h"

CInven::CInven(void)
{
}

CInven::~CInven(void)
{
}

void CInven::Initialize(void)
{
	//ÁÂÇ¥°ü·Ã
	m_Info.vPos.x = 400;
	m_Info.vPos.y =0;
	m_Info.vPos.z = 0;

	m_Info.vCenter = D3DXVECTOR3(0.f,0.f,0.f);
	D3DXMatrixTranslation(&m_Info.matTrans,m_Info.vPos.x ,m_Info.vPos.y,m_Info.vPos.z);
	m_Info.matWorld = m_Info.matTrans;
	
	//Ã¢¶ç¿ì±â 
	m_fTime = 0;
	m_bSwitch = false;

}

void CInven::Progress(void)
{
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PUSH_KEY(KEY_I) && m_fTime > 0.3f)
	{
		CSoundMgr::GetInstance()->SoundPlay(2,0);
		m_fTime = 0;
		//À¯Àú °ÈÁö¸¶
		m_bNotWalk = SwitchSwap(m_bNotWalk);
		//ÀÎº¥ ÄÑ°í ²ô°í
		m_bSwitch = SwitchSwap(m_bSwitch);
	}
}

void CInven::Render(void)
{
	if( m_bSwitch )
	{
		m_PlayerStat = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->GetStat(); //½ºÅÝ¾ò¾î¿È, Àåºñ³¢¸é ½ºÅÝÀû¿ë

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_INVEN, OBJECT_STATEID_INVEN_INVEN)
			, NULL, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CInven::Release(void)
{

}

CObj* CInven::Clone( void )
{
	return new CInven(*this);
}
