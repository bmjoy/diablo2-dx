#include "StdAfx.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Defines.h"


CRectMgr::CRectMgr(void)
{
	Initialize();
}

void	CRectMgr::Initialize(void)
{
	D3DXMatrixIdentity(&m_matWorld);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/rect.png",TEXTYPE_SINGLE,OBJECT_SETRECT);
}
void	CRectMgr::Render(NEWRECT	rc, int id)
{
	RECT		rcImg;
	if( id == RECT_ID_OBJ)
	{
		D3DXMatrixTranslation(&m_matTranslation, rc.fX - (rc.fSizeX+20)/2, rc.fY - (rc.fSizeY+70)/2, 0.f);
		SetRect(&rcImg,0,0,int(rc.fSizeX+20),int(rc.fSizeY+70));
	}
	else if( id == RECT_ID_ATK)
	{
		D3DXMatrixTranslation(&m_matTranslation, rc.fX - rc.fSizeX/2, rc.fY - rc.fSizeY/2, 0.f);
		SetRect(&rcImg,0,0,int(rc.fSizeX),int(rc.fSizeY));
	}
	else if( id == RECT_ID_CLICK)
	{
		D3DXMatrixTranslation(&m_matTranslation, rc.fX - rc.fSizeX/2, rc.fY - rc.fSizeY/2, 0.f);
		SetRect(&rcImg,0,0,int(rc.fSizeX),int(rc.fSizeY));
	}
	m_matWorld	=	m_matTranslation;
	m_vecCenter		=	D3DXVECTOR3(256.f,256.f,0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SETRECT),&rcImg,0,0,D3DCOLOR_ARGB(255,255,255,255));
}

void CRectMgr::Release(void)
{
}

CRectMgr::~CRectMgr(void)
{
	Release();
}
