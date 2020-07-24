#include "StdAfx.h"
#include "Yuusha.h"
#include "SoundMgr.h"
//ACT2 사막에서 해매는 설정
CYuusha::CYuusha(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
{
}

CYuusha::~CYuusha(void)
{
}

void CYuusha::Initialize(void)
{
	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);
	m_Info.vPos = D3DXVECTOR3(1700.f,700.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	//오브젝트의 RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 7;
	m_fTime = 0;
	m_bSwitch = false;

	//퀘스트창
	rcTalk.fSizeX = 600;
	rcTalk.fSizeY = 150;
	rcTalk.fX = 300;
	rcTalk.fY = 75;

	talk1 = false;
	talk2 = false;
	talkend = false;

}

void CYuusha::Progress(void)
{
	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	m_Info.vPos.x -= fX;
	m_Info.vPos.y -= fY;

	m_ObjRect.fX = m_Info.vPos.x;
	m_ObjRect.fY = m_Info.vPos.y;

	//모션 프레임 관련
	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	
	if(m_fFrame > m_iMaxCnt)
	{
			m_fFrame = 0.f;	 
	}

	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PtInRect(&GetObjRect(),MousePt))
	{	//용사를 클릭했을때
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				if( m_bNotWalk == false)
				{
					CSoundMgr::GetInstance()->SoundPlay(28,0);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					SwitchSwap(&m_bNotWalk);
				}
				talk1 = true;
				SwitchSwap(&m_bSwitch); //대화창을 띄운다
				m_fTime = 0;
			}
	}

	//대화창
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcTalk),MousePt)) 
		{	//대화창을 누르면
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{	
				//퀘스트3 대화 
				if( CQuestMgr::GetInstance()->GetQuestNow() == 3 && talk1 == true && talk2 == false)
				{
					talk1 = false;
					talk2 = true;
					m_fTime = 0;
				}
				else if(CQuestMgr::GetInstance()->GetQuestNow() == 3 && talk2 == true && talk1 == false)
				{
					talk2 = false;
					talkend = true;
					CQuestMgr::GetInstance()->SetQuestNow(); //퀘 4로
					m_fTime = 0;
				}
				//퀘스트4 대화
				//퀘스트중일때
				if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//퀘스트를 끝냈을때
				if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() == 5 && talk1 == true && talk2 == false)
				{
					talk1 = false;
					talk2 = true;
					m_fTime = 0;
				}
				if(CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() == 5 && talk2 == false && talk1 == false)
				{		
					m_fTime = 0;
					CQuestMgr::GetInstance()->SetQuestNow();
					talkend = true;
				}		
				//퀘스트 5일때
				if( CQuestMgr::GetInstance()->GetQuestNow() == 5 && CQuestMgr::GetInstance()->GetKillCount3() != 1 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//퀘스트 9일때
				if( CQuestMgr::GetInstance()->GetQuestNow() == 9)
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//모든 대화가 끝나면
				if( m_bNotWalk == true && talkend == true)
				{
					talkend = false;
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					SwitchSwap(&m_bSwitch); //대화창 끄기
					m_fTime = 0;
				}
			}
		}
	}
}

void CYuusha::Render(void)
{

	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //이동시키는 함수
	m_Info.matWorld = m_Info.matTrans; //월드행렬에 적용
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_YUUSHA, OBJECT_STATEID_YUUSHA_YUUSHA, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	if(m_bSwitch)
	{
		D3DXMatrixTranslation(&m_TransShop,257,256,0);
		m_WorldShop = m_TransShop;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_YUUSHA, OBJECT_STATEID_YUUSHA_TALK)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		//퀘스트3 대화 textrender
		if(CQuestMgr::GetInstance()->GetQuestNow() == 3 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"아, 모험자님 잘 오셨어요!\n\n제가 모험자님을 찾았던 이유는\n제 친구 소닉이 나갔다가 돌아오지 않고 있어요\n한 번 찾아봐 주실 수 있으세요?" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 3 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"소닉이 카우들이 있는곳으로 가보겠다고 말했었어요\n카우들은 마을 밖 남서쪽에 있어요!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		//퀘스트4 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"소닉아 어디갔니..." );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 4 && talk1 && CQuestMgr::GetInstance()->GetKillCount2() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"아니? 그것은..\n\n소닉의 신발??\n소닉에게 뭔가 안 좋은일이 생긴것이 틀림없어요!!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 4 && !talk1 && CQuestMgr::GetInstance()->GetKillCount2() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"저도 소닉을 찾으러 가야겠어요!\n아이작에게도 알려주세요!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talk2 = false;
		}
		//퀘스트5 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == 5 && CQuestMgr::GetInstance()->GetKillCount3() != 1 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"곧 출발하겠습니다!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		//퀘스트9 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == 9)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"소닉을 구해주셔서 정말 고마워요!\n그런데 아이작은 어디가고 번쩍이는 사람만 있네요\n눈 아프게시리..." );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
	}

	//렉트보이기
	//CRectMgr::GetInstance()->Render(rcTalk,RECT_ID_CLICK);
}

void CYuusha::Release(void)
{

}

CObj* CYuusha::Clone(void)
{
	return new CYuusha(*this);
}

void CYuusha::SwitchSwap(bool* bSwitch)
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