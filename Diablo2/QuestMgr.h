#pragma once
#include "singleton.h"
#include "Defines.h"
#include "Device.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "TimeMgr.h"
#include "Player.h"
#include "TextMgr.h"
#include "BackGround.h"
#include "SoundMgr.h"

class CQuestMgr :
	public CSingleTon<CQuestMgr>
{
private:
	int		m_iQuestNow; //퀘스트 상태(진행도)
	int		m_iKillCount1; //퀘스트1 킬 카운트
	int		m_iKillCount2; //퀘스트2 킬 카운트
	int		m_iKillCount3; //보스 킬 카운트

	bool	m_bSwitchAlert; //m_fAlertTime 돌리는 스위치
	bool	m_bTalkSwitch;		//플레이어 대화창 스위치
	float	m_fAlertTime; //퀘스트 알림창 뜨는 시간
	float	m_fTime; //클릭 딜레이
	float	m_fDistance;
	float	m_fAngle;

	bool	m_bQ4Close;
	bool	m_bQ6Close;
	bool	m_bQ8Close;

	bool	m_bMusic1;
	bool	m_bMusic2;

	D3DXMATRIX	m_TransPlayerTalk;
	D3DXMATRIX	m_WorldPlayerTalk;

	D3DXMATRIX	m_TransQuestNavi;
	D3DXMATRIX	m_WorldQuestNavi;
	
	//퀘스트 장소를 알려주는 화살표
	D3DXMATRIX	m_TransArrow;
	D3DXMATRIX	m_WorldArrow;
	D3DXMATRIX	m_RotzArrow;

	D3DXMATRIX	m_TransQuestAlert;
	D3DXMATRIX	m_WorldQuestAlert;

	D3DXVECTOR3	m_vecPlayerPos; //플레이어의 지금 위치
	D3DXVECTOR3	m_vecDestPos;	//목적지 위치
	D3DXVECTOR3	m_vecLook; //화살표가 바라보는 방향
	D3DXVECTOR3	m_vecDir; //목적지를 바라보는 방향

	NEWRECT			rcPlayerTalk;
public:
	int		GetQuestNow(void) { return m_iQuestNow; }
	int		GetKillCount1(void) { return m_iKillCount1; }
	int		GetKillCount2(void) { return m_iKillCount2; }
	int		GetKillCount3(void) { return m_iKillCount3; }
			
	void	SetQuestNow(void) { m_iQuestNow +=1; }
	void	SetKillCount1(void) { m_iKillCount1 += 1; }
	void	SetKillCount2(void) { m_iKillCount2 += 1; }
	void	SetKillCount3(void) { m_iKillCount3 += 1; }
	
	void SwitchSwap(bool* bSwitch);
	RECT GetClickRect(NEWRECT nrc);

public:
	void	Initialize(void);
	void	Progress(void);
	void	Release(void);
	void	Render(void);

public:
	friend CQuestMgr* CSingleTon<CQuestMgr>::GetInstance();
public:
	CQuestMgr(void);
	~CQuestMgr(void);
};


//TCHAR		szHp[128];
//ZeroMemory(&szHp, sizeof(szHp));
//wsprintf(szHp, L"생명: %d / %d", m_PlayerStat.iHp, m_PlayerStat.iMaxHp);
//CTextMgr::GetInstance()->MakeText(szHp,20,500,0.6f,0.6f);


//D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //이동시키는 함수
//m_Info.matWorld = matTrans; //월드행렬에 적용
//CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
//CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_DIE2)
//										  , NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));