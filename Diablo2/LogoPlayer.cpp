#include "StdAfx.h"
#include "LogoPlayer.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CLogoPlayer::CLogoPlayer(void)
: m_fAngle(0.f)
, m_fTime(0.f)
{
}

CLogoPlayer::CLogoPlayer(const INFO& Info)
: CObj(Info)
, m_fAngle(0.f)
, m_fTime(0.f)
{
}

CLogoPlayer::~CLogoPlayer(void)
{
}

void CLogoPlayer::Initialize( void )
{
	m_Info.vPos = D3DXVECTOR3(400.0f, 300.0f, 0.0f);
	m_Info.vCenter = D3DXVECTOR3(400.0f, 300.f, 0.0f);

	/*m_Info.vPos.x = 400.0f;
	m_Info.vPos.y = 300.0f;
`	m_Info.vPos.z = 0.0f;*/
	m_Info.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	
}

void CLogoPlayer::Progress( void )
{
	
	D3DXMATRIX			matTrans;
	D3DXMATRIX			matRotZ;

	//m_Info.vPos.x += 100.0f * CTimeMgr::GetInstance()->GetPixelPerSec();

	//m_fAngle += 90.0f * CTimeMgr::GetInstance()->GetPixelPerSec();

	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();	

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);

	m_Info.matWorld = matRotZ * matTrans;
}

void CLogoPlayer::Render( void )
{
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_LOGO_PLAYER)
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CLogoPlayer::Release( void )
{

}

CObj* CLogoPlayer::Clone( void )
{
	return new CLogoPlayer(*this);
}
