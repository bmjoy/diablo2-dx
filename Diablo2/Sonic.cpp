#include "StdAfx.h"
#include "Sonic.h"

CSonic::CSonic(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
{
}

CSonic::~CSonic(void)
{
}

void CSonic::Initialize(void)
{
	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);
	m_Info.vPos = D3DXVECTOR3(9000.f,1800.f, 0.f); //초기위치(보스 있는곳)
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	m_vTownPos = D3DXVECTOR3(1750.f,730.f, 0.f);

	//오브젝트의 RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 2;
	m_fTime = 0;
	m_bSwitch = false;

	//대화창
	rcTalk.fSizeX = 600;
	rcTalk.fSizeY = 150;
	rcTalk.fX = 300;
	rcTalk.fY = 75;

	talk1 = false;
	talk2 = false;
	talkend = false;

}

void CSonic::Progress(void)
{
	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	m_Info.vPos.x -= fX;
	m_Info.vPos.y -= fY;
	m_vTownPos.x -= fX;
	m_vTownPos.y -= fY;

	//잡혀있는 소닉 rect
	if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7 && CQuestMgr::GetInstance()->GetKillCount3() == 1 )
	{
		m_ObjRect.fX = m_Info.vPos.x;
		m_ObjRect.fY = m_Info.vPos.y;
	}

	if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST9 )
	{
		m_ObjRect.fX = m_vTownPos.x;
		m_ObjRect.fY = m_vTownPos.y;
	}

	//모션 프레임 관련
	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	
	if(m_fFrame > m_iMaxCnt)
	{
			m_fFrame = 0.f;	 
	}

	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PtInRect(&GetObjRect(),MousePt))
	{	//소닉을 클릭했을때
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				if( m_bNotWalk == false)
				{
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					SwitchSwap(&m_bNotWalk);
				}
				talk1 = true;
				SwitchSwap(&m_bSwitch); //대화창을 띄운다
				m_fTime = 0;
			}
	}

	//대화창 떠있는 상황
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcTalk),MousePt)) 
		{	//대화창을 누르면
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				//퀘스트7 대화(단일)
				if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7 && CQuestMgr::GetInstance()->GetKillCount3() == 1  )
				{
					talk1 = false;
					talkend = false;
					CQuestMgr::GetInstance()->SetQuestNow(); //퀘스트8
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//퀘스트9 대화
				if( CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk1 == true && talk2 == false)
				{
					talk1 = false;
					talk2 = true;
					m_fTime = 0;
				}
				else if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk2 == true && talk1 == false)
				{
					talk2 = false;
					talkend = true;
					m_fTime = 0;
				}

				//모든 대화가 끝나면
				if( m_bNotWalk == true && talkend == true)
				{
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
			}
		}
	}
}

void CSonic::Render(void)
{
	//보스있는곳에 하나
	if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7)
	{
	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //이동시키는 함수
	m_Info.matWorld = m_Info.matTrans; //월드행렬에 적용
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SONIC, OBJECT_STATEID_SONIC_HELP, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	//보스잡고나서 마을에
	if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST8 || CQuestMgr::GetInstance()->GetQuestNow() == 9)
	{
		m_iMaxCnt = 4;
		//D3DXMatrixIdentity(&m_Info.matTrans);
		//D3DXMatrixIdentity(&m_Info.matWorld);
		D3DXMatrixTranslation(&m_TransTown,m_vTownPos.x, m_vTownPos.y, m_vTownPos.z); //마을안으로 이동
		m_WorldTown = m_TransTown; //월드행렬에 적용
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldTown);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SONIC, OBJECT_STATEID_SONIC_NOMAL, int(m_fFrame))
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//대화창 render
	if(m_bSwitch)
	{
		D3DXMatrixTranslation(&m_TransShop,257,256,0);
		m_WorldShop = m_TransShop;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SONIC, OBJECT_STATEID_SONIC_TALK)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		//퀘스트 7 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7 && CQuestMgr::GetInstance()->GetKillCount3() == 1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"구해주셔서 감사합니다!!\n정말 죽는줄 알았어요..\n마을에서 다시 만나요!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}

		//퀘스트9 대화
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"모험가님! 구해주셔서 정말 고맙습니다!\n\n이 은혜 잊지 않을께요!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"그런데 저 옆에 번쩍거리는 사람은 누구죠?");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
	}

	//렉트보이기
	//CRectMgr::GetInstance()->Render(rcTalk,RECT_ID_CLICK);
}

void CSonic::Release(void)
{

}

CObj* CSonic::Clone(void)
{
	return new CSonic(*this);
}

void CSonic::SwitchSwap(bool* bSwitch)
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