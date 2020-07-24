#include "StdAfx.h"
#include "LogoProto.h"

#include "LogoPlayer.h"
#include "LogoMonster.h"

CLogoProto::CLogoProto(void)
{
	SetProto();
}

CLogoProto::~CLogoProto(void)
{
	
}


void CLogoProto::SetProto(void)
{	
	INFO				Info;
	ZeroMemory(&Info, sizeof(Info));

	Info.vPos = D3DXVECTOR3(WINSIZEX / 2.f, WINSIZEY / 2.f, 0.f);
	Info.vLook = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&Info.matWorld);	

	m_mapObj.insert(make_pair(OBJECT_LOGO_PLAYER, new CLogoPlayer(Info)));	
	m_mapObj.insert(make_pair(OBJECT_LOGO_MONSTER, new CLogoMonster(Info)));
}


