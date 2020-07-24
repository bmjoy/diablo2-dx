#include "StdAfx.h"
#include "Act2.h"

#include "TextureMgr.h"
#include "Act2Proto.h"
#include "ObjMgr.h"
#include "StateMgr.h"
#include "KeyMgr.h"

CAct2::CAct2(void)
{
}

CAct2::~CAct2(void)
{
	Release();
}

void CAct2::Initialize(void)
{
//Study #2
//시작할때마다 Instance를 날려버리기 때문에 기존에 저장된 m_MapObj이나 m_mapTex들은 죄다 날아간다

	CObjMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	m_pObjProto = new CAct2Proto;

	
	//타일
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Tile/Tile0%d.png", TEXTYPE_MULTI, OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, TILENUM);
	//오브젝트
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Object/%d.png", TEXTYPE_MULTI, OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_OBJECT, OBJNUM);

	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/1/01_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND1, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/2/02_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND2, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/3/03_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND3, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/4/04_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND4, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/5/05_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND5, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/6/06_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND6, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/7/07_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND7, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/8/08_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND8, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/9/09_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND9, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/10/10_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND10, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/11/11_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND11, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/12/12_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND12, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/13/13_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND13, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/14/14_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND14, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/15/15_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND15, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/16/16_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND16, 8);

	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/1/01_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN1, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/2/02_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN2, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/3/03_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN3, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/4/04_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN4, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/5/05_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN5, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/6/06_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN6, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/7/07_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN7, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/8/08_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN8, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/9/09_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN9, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/10/10_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN10, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/11/11_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN11, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/12/12_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN12, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/13/13_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN13, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/14/14_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN14, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/15/15_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN15, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/16/16_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN16, 8);
								

	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/1/01_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK1, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/2/02_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK2, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/3/03_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK3, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/4/04_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK4, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/5/05_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK5, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/6/06_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK6, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/7/07_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK7, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/8/08_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK8, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/9/09_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK9, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/10/10_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK10, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/11/11_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK11, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/12/12_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK12, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/13/13_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK13, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/14/14_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK14, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/15/15_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK15, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/16/16_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK16, 18);

	CObjMgr::GetInstance()->AddObject(OBJECT_BACKGROUND, m_pObjProto);
	CObjMgr::GetInstance()->AddObject(OBJECT_PLAYER, m_pObjProto);	


}

void CAct2::Progress(void)
{
	//나중에 포탈로 구현
	//Player에 있는 key관리 함수에서 하려니깐 잘안되서 넘겨뻐림;;
	if(PUSH_KEY(KEY_F1))
	{
		//플레이어 정보를 따로 저장하고 넘겨야한다
		CStateMgr::GetInstance()->SetState(STATEID_ACT1);
		return;	
	}	
	CObjMgr::GetInstance()->Progress();
}

void CAct2::Render(void)
{
	CObjMgr::GetInstance()->Render();
}

void CAct2::Release(void)
{
	SAFE_DELETE(m_pObjProto);
}

CStateObj* CAct2::Clone(void)
{
	return new CAct2(*this);
}
