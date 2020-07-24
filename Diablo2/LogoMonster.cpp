#include "StdAfx.h"
#include "LogoMonster.h"

#include "Device.h"
#include "ObjMgr.h"

#include "TextureMgr.h"


CLogoMonster::CLogoMonster(void)
{
}

CLogoMonster::CLogoMonster(const INFO& Info)
: CObj(Info)
{

}

CLogoMonster::~CLogoMonster(void)
{
}

void CLogoMonster::Initialize( void )
{
	m_Info.vCenter = D3DXVECTOR3(128.0f, 128.0f, 0.f);	
}

void CLogoMonster::Progress( void )
{

	D3DXMATRIX			matRotZ;
	D3DXMATRIX			matTrans;

	INFO Info = CObjMgr::GetInstance()->GetInfo(OBJECT_LOGO_PLAYER);

	m_Info.vDir = Info.vPos - m_Info.vPos;

	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);

	float	fAngle = acosf(D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook));

	if(Info.vPos.y < m_Info.vPos.y)		
	{
		fAngle = D3DXToRadian(360.f) - fAngle;
	}

	m_Info.vPos += m_Info.vDir * 0.3f;
		
	D3DXMatrixRotationZ(&matRotZ, fAngle);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);

	m_Info.matWorld = matRotZ * matTrans;
}

void CLogoMonster::Render( void )
{
	RECT		rc = {400, 250, 600, 450};

	/*CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_LOGO_MONSTER)
		, / *렉트의 포인터* /, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));*/

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_LOGO_MONSTER)
		, NULL, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
}

void CLogoMonster::Release( void )
{

}

CObj* CLogoMonster::Clone( void )
{
	return new CLogoMonster(*this);
}
