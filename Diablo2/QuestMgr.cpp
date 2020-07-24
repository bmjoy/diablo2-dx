#include "StdAfx.h"
#include "QuestMgr.h"

CQuestMgr::CQuestMgr(void)
: m_fTime(0.f), m_fAlertTime(0.f) //퀘스트 알림창 뜨는 시간
{
}

CQuestMgr::~CQuestMgr(void)
{
}

void CQuestMgr::Initialize(void)
{
	m_iQuestNow = 0; //퀘스트 상태(진행도)
	m_iKillCount1 = 0; //퀘스트1 킬 카운트
	m_iKillCount2 = 0; //퀘스트2 킬 카운트
	m_iKillCount3 = 0; //보스 킬 카운트

	m_bSwitchAlert = false; //m_fAlertTime 돌리는 스위치
	m_bTalkSwitch = true;

	m_bQ4Close	 = false; //소닉 신발을 찾았다! 알림 끄기
	m_bQ6Close  = false;
	m_bQ8Close	 = false;

	m_bMusic1 = false;
	m_bMusic2 = true;

	rcPlayerTalk.fSizeX = 600;
	rcPlayerTalk.fSizeY = 150;
	rcPlayerTalk.fX = 300;
	rcPlayerTalk.fY = 75;
	
	m_fDistance = 0.f;
	m_fAngle = 0.f;
	
	m_vecLook = D3DXVECTOR3(1.f, 0.f, 0.f);
}

void CQuestMgr::Progress(void)
{
	//플레이어 대화창 넘길때
	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	//치트키(임시)
	if(PUSH_KEY(KEY_1) && m_fTime > 0.3f)
	{
		++m_iKillCount1;
		m_fTime = 0;
	}

	if(PUSH_KEY(KEY_2) && m_fTime > 0.3f)
	{
		++m_iKillCount2;
		m_fTime = 0;
	}

	if(PUSH_KEY(KEY_3) && m_fTime > 0.3f)
	{
		++m_iKillCount3;
		m_fTime = 0;
	}
	if(PUSH_KEY(KEY_4) && m_fTime > 0.3f)
	{
		++m_iQuestNow;
		m_fTime = 0;
	}

	if(PtInRect(&GetClickRect(rcPlayerTalk),MousePt)) 
	{	//대화창 클릭했을때
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				if( m_iQuestNow == QUEST_NOW_QUEST0 )
				{
					SwitchSwap(&m_bTalkSwitch);
					m_iQuestNow++;
					m_fTime = 0;
				}
			}
	}

//////////////////////퀘스트 네비(화살표)//////////////////
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //용사
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //아이작
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(535); //펄른마법사
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2634); //보스
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2613); //카우

	//플레이어의 위치
	m_vecPlayerPos = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->GetInfo().vPos;

	//퀘스트별로 목적지가 다르기 때문에
	if( m_iQuestNow == QUEST_NOW_QUEST0)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //아이작
	}
	if( m_iQuestNow == QUEST_NOW_QUEST1)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //아이작
	}
	if( m_iQuestNow == QUEST_NOW_QUEST2 && m_iKillCount1 != 5)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(535); //펄른마법사
	}
	if( m_iQuestNow == QUEST_NOW_QUEST2 && m_iKillCount1 == 5)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //아이작
	}
	if( m_iQuestNow == QUEST_NOW_QUEST3 )
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //용사
	}
	if( m_iQuestNow == QUEST_NOW_QUEST4 && m_iKillCount2 != 5 )
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2613); //카우
	}
	if( m_iQuestNow == QUEST_NOW_QUEST4 && m_iKillCount2 == 5 )
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //용사
	}
	if( m_iQuestNow == QUEST_NOW_QUEST5)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //아이작
	}
	if( m_iQuestNow == QUEST_NOW_QUEST6)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2634); //보스
	}
	if( m_iQuestNow == QUEST_NOW_QUEST7 && m_iKillCount3 == 0)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2634); //보스
	}
	if( m_iQuestNow == QUEST_NOW_QUEST7 && m_iKillCount3 == 1)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //용사(마을)
	}
	if( m_iQuestNow == QUEST_NOW_QUEST8)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //용사(마을)
	}	
	if( m_iQuestNow == QUEST_NOW_QUEST9)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //용사(마을)
	}	

	m_vecDir  = m_vecDestPos - m_vecPlayerPos;
	m_fDistance = D3DXVec3Length(&m_vecDir);
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);

	m_fAngle = acosf(D3DXVec3Dot( &m_vecLook, &m_vecDir));
	if( m_vecDestPos.y < m_vecPlayerPos.y)
	{
		m_fAngle = 2 * D3DX_PI - m_fAngle;
	}

////////////////////////퀘스트 알림////////////////////////
	//몹을 다섯마리 잡았을때 소닉의 신발을 찾았다고 알린다
	if(m_iKillCount2 == 5 && m_bQ4Close == false )
	{
		m_bSwitchAlert = true;
	}
	//퀘스트6 소닉 근처로 가면 발견했다고 뜬다
	if(m_fDistance < 500.f && m_bQ6Close == false && m_iQuestNow == QUEST_NOW_QUEST6 )
	{
		m_bSwitchAlert = true;
	}
	//퀘스트8 -> 9로 넘어가기 마을로 돌아가세요!
	if(m_fDistance < 500.f && m_bQ8Close == false && m_iQuestNow == QUEST_NOW_QUEST8 )
	{
		m_bSwitchAlert = true;
	}
	//퀘스트 알림창은 3초만 뜬다
	if(m_fAlertTime > 3.f)
	{
		m_bSwitchAlert = false;
		m_fAlertTime = 0.f;

		if(m_iQuestNow == QUEST_NOW_QUEST6)
		{
			SetQuestNow();
		}
		if(m_iQuestNow == QUEST_NOW_QUEST8)
		{
			m_bMusic1 = true;
			SetQuestNow();
		}
	}
/////////////////////////////////////////////////////////
	if(m_bMusic1)
	{
		CSoundMgr::GetInstance()->SoundStop(1);
		CSoundMgr::GetInstance()->SoundPlay(0, 1);	
		m_bMusic1 = false;
	}
	if(m_bMusic2 && m_iQuestNow == QUEST_NOW_QUEST6)
	{
		CSoundMgr::GetInstance()->SoundStop(0);
		CSoundMgr::GetInstance()->SoundPlay(1, 1);
		m_bMusic2 = false;
	}

}

void CQuestMgr::Render(void)
{	
	//퀘스트 네비게이터(알림)
	D3DXMatrixTranslation(&m_TransQuestNavi,650,100,0);
	m_WorldQuestNavi = m_TransQuestNavi;
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldQuestNavi);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALRAM)
		, NULL, NULL, NULL, D3DCOLOR_ARGB(100, 255, 255, 255));
	
	//방향 알려주는 화살표
	D3DXMatrixTranslation(&m_TransArrow,720,330,0);
	D3DXMatrixRotationZ(&m_RotzArrow, m_fAngle);
	m_WorldArrow = m_RotzArrow * m_TransArrow;
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldArrow);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ARROW)
		, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//거리 (적절한 퀘스트 있을때만 보여줌)
	TCHAR		szText[128];
	ZeroMemory(&szText, sizeof(szText));
	wsprintf(szText, L"남은거리\n%d m",int(m_fDistance/10) );
	CTextMgr::GetInstance()->MakeText(szText,710,370,0.7f,0.8f);

	if( m_iQuestNow == QUEST_NOW_QUEST1 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 1 \n\n오른쪽으로 이동하여 \n아이작과 대화하세요" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST2 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 2 \n\n맵의 북동쪽으로 가세요 \n펄른 마법사 (%d/5)",m_iKillCount1);
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
		if(m_iKillCount1 == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"마을로 돌아가서\n아이작과 대화하세요!");
			CTextMgr::GetInstance()->MakeText(szText,650,150,0.7f,0.7f);
		}
	}
	if( m_iQuestNow == QUEST_NOW_QUEST3 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 3 \n\n아이작 옆에 있는 \n용사와 대화하세요!" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST4 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 4 \n\n카우들을 처치하세요 \n카우 (%d/5)",m_iKillCount2 );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
		if(m_iKillCount2 == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"마을로 돌아가서\n용사와 대화하세요!!");
			CTextMgr::GetInstance()->MakeText(szText,650,150,0.7f,0.7f);
		}
	}
	if( m_iQuestNow == QUEST_NOW_QUEST5 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 5 \n\n아이작에게 소닉을 \n찾으러 간다고 \n전해주세요" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST6 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 6\n      B O S S \n\n필드 동쪽 끝으로\n 이동하세요" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if(m_iQuestNow == QUEST_NOW_QUEST7)
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 7\n      B O S S \n\n증오의 군주\n메피스토를 처치하세요\n메피스토 (%d/1)",m_iKillCount3 );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
		if(m_iKillCount3 == 1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"메피스토를 \n처치했습니다!\n소닉을 풀어주세요");
			CTextMgr::GetInstance()->MakeText(szText,650,200,0.7f,0.7f);
		}
	}
	if( m_iQuestNow == QUEST_NOW_QUEST8 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 8\n소닉을 무사히\n구출했습니다\n마을로 돌아가세요" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST9 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 9\n      E N D \n   소닉이 무사히\n   돌아왔습니다!\n   마을사람들과\n   대화를 나눠보세요!" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}

////////////////////////////////////////////////////////////////////////////
	if(m_bTalkSwitch)
	{
		D3DXMatrixTranslation(&m_TransPlayerTalk,0,0,0);
		m_WorldPlayerTalk = m_TransPlayerTalk;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldPlayerTalk);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_PLAYERTALK)
			, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if( m_iQuestNow == QUEST_NOW_QUEST0 && m_bTalkSwitch == true)
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"디아블로2에 오신것을 환영합니다\n 오른쪽으로 이동하여 아이작과 대화하세요!" );
		CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
	}

	//퀘스트4 알림
	if(m_bSwitchAlert && m_iQuestNow == QUEST_NOW_QUEST4)
	{
		m_fAlertTime += CTimeMgr::GetInstance()->GetPixelPerSec();
		D3DXMatrixTranslation(&m_TransQuestAlert,260,50,0);
		m_WorldQuestAlert = m_TransQuestAlert;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldQuestAlert);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALERT)
			, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"소닉의 신발을 발견했다!");
		CTextMgr::GetInstance()->MakeText(szText,265,60,0.8f,0.8f);
		m_bQ4Close = true;
	}
	
	//퀘스트6 알림
	if(m_bSwitchAlert && m_iQuestNow == QUEST_NOW_QUEST6)
	{
		m_fAlertTime += CTimeMgr::GetInstance()->GetPixelPerSec();
		D3DXMatrixTranslation(&m_TransQuestAlert,260,50,0);
		m_WorldQuestAlert = m_TransQuestAlert;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldQuestAlert);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALERT)
			, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"잡혀있는 소닉을 발견했다!");
		CTextMgr::GetInstance()->MakeText(szText,265,60,0.8f,0.8f);
		m_bQ6Close = true;
	}

	//퀘스트8 알림
	if(m_bSwitchAlert && m_iQuestNow == QUEST_NOW_QUEST8)
	{
		m_fAlertTime += CTimeMgr::GetInstance()->GetPixelPerSec();
		D3DXMatrixTranslation(&m_TransQuestAlert,260,50,0);
		m_WorldQuestAlert = m_TransQuestAlert;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldQuestAlert);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALERT)
			, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"마을 사람들과 대화를 나눠보세요!");
		CTextMgr::GetInstance()->MakeText(szText,265,60,0.8f,0.8f);
		m_bQ6Close = true;
	}

		//CRectMgr::GetInstance()->Render(rcPlayerTalk,RECT_ID_CLICK);
}

void CQuestMgr::Release(void)
{

}

void CQuestMgr::SwitchSwap(bool* bSwitch)
{
	if(*bSwitch)
	{
		*bSwitch = false;
	}
	else
	{
		*bSwitch = true;
	}

}

RECT CQuestMgr::GetClickRect(NEWRECT nrc)
{
	RECT rc = {
		long( nrc.fX - nrc.fSizeX/2 ),
		long( nrc.fY - nrc.fSizeY/2 ),
		long( nrc.fX + nrc.fSizeX/2 ),
		long( nrc.fY + nrc.fSizeY/2 ),
	};
	return rc;
}