#include "StdAfx.h"
#include "MainGame.h"

#include "Device.h"
#include "StateMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "AStar.h"
#include "RectMgr.h"
#include "ScrollMgr.h"
#include "QuestMgr.h"
#include "TextMgr.h"
#include "SoundMgr.h"
#include "RandomMgr.h"



CMainGame::CMainGame(void)
: m_pDevice(CDevice::GetInstance())
, m_pStateMgr(CStateMgr::GetInstance())
, m_iCnt(0)
, m_fData(0.f)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}


HRESULT CMainGame::Initialize(void)
{
	

	if(FAILED(m_pDevice->Initialize()))
	{
		ERRORCHK(L"장치초기화실패");
		return E_FAIL;
	}

	if(FAILED(m_pStateMgr->SetState(STATEID_LOGO)))
	{
		ERRORCHK(L"상태객체생성실패");
		return E_FAIL;
	}

	return S_OK;
}


void CMainGame::Progress(void)
{
	CTimeMgr::GetInstance()->SetPixelPerSec();
	CKeyMgr::GetInstance()->SetKeyCheck();

	m_pStateMgr->Progress();	
}

void CMainGame::Render(void)
{
	++m_iCnt;

	m_fData += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(m_fData > 1.f)
	{
		wsprintf(m_szFps, L"FPS:%d", m_iCnt);
		m_iCnt = 0;
		m_fData = 0.f;
	}

	RECT		rcFont = {0};
	D3DXMATRIX			matIden;

	D3DXMatrixIdentity(&matIden);


	// 지운다.
	m_pDevice->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pDevice->GetDevice()->BeginScene();

	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	// 객체들을 그린다.
	m_pStateMgr->Render();

	m_pDevice->GetSprite()->SetTransform(&matIden);
	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite()
		, m_szFps, lstrlen(m_szFps), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 113, 0, 0));

	m_pDevice->GetSprite()->End();



	m_pDevice->GetDevice()->EndScene();

	// 전면버퍼로 보여준다.
	m_pDevice->GetDevice()->Present(NULL, NULL, NULL, NULL);
	
}


void CMainGame::Release(void)
{
	m_pDevice->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
	m_pStateMgr->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CAStar::GetInstance()->DestroyInstance();
	CScrollMgr::GetInstance()->DestroyInstance();
	CQuestMgr::GetInstance()->DestroyInstance();
	CRectMgr::GetInstance()->DestroyInstance();
	CTextMgr::GetInstance()->DestroyInstance();
	CRandomMgr::GetInstance()->DestroyInstance();
	
}

