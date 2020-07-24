#include "StdAfx.h"
#include "Logo.h"

#include "LogoProto.h"
#include "ObjMgr.h"

#include "TextureMgr.h"
#include "KeyMgr.h"

#include "StateMgr.h"
#include "SoundMgr.h"

CLogo::CLogo(void)
{
}

CLogo::CLogo(int iData0, int iData1)
: CStateObj(iData0, iData1)
{
	
}

CLogo::~CLogo(void)
{
	Release();
}

void CLogo::Initialize( void )
{
	m_pObjProto = new CLogoProto;

	m_pObjMgr->AddObject(OBJECT_LOGO_PLAYER, m_pObjProto);
//	m_pObjMgr->AddObject(OBJECT_LOGO_MONSTER, m_pObjProto);

	CTextureMgr::GetInstance()->AddTexture(L"../Texture/main.png", TEXTYPE_SINGLE, OBJECT_LOGO_PLAYER);

	CSoundMgr::GetInstance()->Init();
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Logo/introedit.wav");
	CSoundMgr::GetInstance()->SoundPlay(0, 1);
	//CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/AKIHA_AKI00_000.png", TEXTYPE_SINGLE, OBJECT_LOGO_MONSTER);
}

void CLogo::Progress( void )
{
	if(PUSH_KEY(KEY_LBUTTON))
	{
		CStateMgr::GetInstance()->SetState(STATEID_ACT1);
		return;		
	}	
	if(PUSH_KEY(KEY_RBUTTON))
	{
		CStateMgr::GetInstance()->SetState(STATEID_ACT2);
		return;		
	}
	m_pObjMgr->Progress();
}

void CLogo::Render( void )
{
	m_pObjMgr->Render();
}

void CLogo::Release( void )
{
	SAFE_DELETE(m_pObjProto);
}

CStateObj* CLogo::Clone( void )
{
	return new CLogo(*this);
}
