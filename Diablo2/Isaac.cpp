#include "StdAfx.h"
#include "Isaac.h"

CIsaac::CIsaac(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
{
}

CIsaac::~CIsaac(void)
{
}

void CIsaac::Initialize(void)
{
	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);
	m_Info.vPos = D3DXVECTOR3(1600.f,600.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	//오브젝트의 RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 10;
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

void CIsaac::Progress(void)
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
	{	//아이작을 클릭했을때
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
				//퀘스트1 대화
				if( CQuestMgr::GetInstance()->GetQuestNow() == 1 && talk1 == true && talk2 == false)
				{
					talk1 = false;
					talk2 = true;
					m_fTime = 0;
				}
				else if(CQuestMgr::GetInstance()->GetQuestNow() == 1 && talk2 == true && talk1 == false)
				{
					talk2 = false;
					talkend = true;
					CQuestMgr::GetInstance()->SetQuestNow();
					m_fTime = 0;
				}

				//퀘스트2 대화
				//퀘스트중일때
				if( CQuestMgr::GetInstance()->GetQuestNow() == 2 && CQuestMgr::GetInstance()->GetKillCount1() != 5 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//퀘스트를 끝냈을때
				if( CQuestMgr::GetInstance()->GetQuestNow() == 2 && CQuestMgr::GetInstance()->GetKillCount1() == 5 && talk1 == true && talk2 == false)
				{
					talk1 = false;
					talk2 = true;
					m_fTime = 0;
				}
				if(CQuestMgr::GetInstance()->GetQuestNow() == 2 && CQuestMgr::GetInstance()->GetKillCount1() == 5 && talk2 == false && talk1 == false)
				{		
					m_fTime = 0;
					CQuestMgr::GetInstance()->SetQuestNow();
					talkend = true;
				}
				
				//퀘스트3 대화
				if( CQuestMgr::GetInstance()->GetQuestNow() == 3 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//퀘스트4 대화
				if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5  )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //대화창 끄기
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//퀘스트5 대화 
				if( CQuestMgr::GetInstance()->GetQuestNow() == 5 && talk1 == true && talk2 == false)
				{
					talk1 = false;
					talk2 = true;
					m_fTime = 0;
				}
				else if(CQuestMgr::GetInstance()->GetQuestNow() == 5 && talk2 == true && talk1 == false)
				{
					talk2 = false;
					talkend = true;
					CQuestMgr::GetInstance()->SetQuestNow(); //퀘 6으로
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

void CIsaac::Render(void)
{
	if( CQuestMgr::GetInstance()->GetQuestNow() == 8 || CQuestMgr::GetInstance()->GetQuestNow() == 9 )
	{
		CDevice::GetInstance()->GetSprite()->End();
		CDevice::GetInstance()->GetDevice()->EndScene();

		CDevice::GetInstance()->GetDevice()->BeginScene();
		CDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		m_iMaxCnt = 60;
		D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //이동시키는 함수
		m_Info.matWorld = m_Info.matTrans; //월드행렬에 적용
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_ISAAC, OBJECT_STATEID_ISAAC_GOD, int(m_fFrame))
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		CDevice::GetInstance()->GetSprite()->End();
		CDevice::GetInstance()->GetDevice()->EndScene();
		CDevice::GetInstance()->GetDevice()->BeginScene();
		CDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else
	{
		D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //이동시키는 함수
		m_Info.matWorld = m_Info.matTrans; //월드행렬에 적용
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_ISAAC, OBJECT_STATEID_ISAAC_ISAAC, int(m_fFrame))
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(m_bSwitch)
	{
		if( CQuestMgr::GetInstance()->GetQuestNow() == 8 || CQuestMgr::GetInstance()->GetQuestNow() == 9 )
		{
			D3DXMatrixTranslation(&m_TransShop,257,256,0);
			m_WorldShop = m_TransShop;
			CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
			CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_ISAAC, OBJECT_STATEID_ISSAC_GTALK)
				, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			D3DXMatrixTranslation(&m_TransShop,257,256,0);
			m_WorldShop = m_TransShop;
			CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
			CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_ISAAC, OBJECT_STATEID_ISAAC_TALK)
				, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		//퀘스트1 대화 textrender
		if(CQuestMgr::GetInstance()->GetQuestNow() == 1 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"안녕하세요 저는 아이작이에요 반갑습니다\n\n모습을 보아하니 혹시 모험가 이신가요?" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 1 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"최근 펄른 마법사들이 마을까지 들어와서 걱정이에요\n필드 북동쪽 끝에 있는 펄른 마법사 군락지에 가셔서\n정리좀 해주시면 정말 고마울거에요!\n참고로 마법은 쓰지 않으니 걱정마세요");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}

		//퀘스트2 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == 2 && CQuestMgr::GetInstance()->GetKillCount1() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"펄른 마법사들을 혼내주세요 ㅜㅜ" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}

		if(CQuestMgr::GetInstance()->GetQuestNow() == 2 && talk1 && CQuestMgr::GetInstance()->GetKillCount1() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"고맙습니다 모험가님!\n덕분에 마을까지 펄른들이 들어오지 않게 됐어요!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 2 && !talk1 && CQuestMgr::GetInstance()->GetKillCount1() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"아! 모험가님\n제 옆에 서있는 용사님이 모험가님을 찾던데\n어서 찾아가 보세요!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talk2 = false;
		}
		//퀘스트3 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == 3 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"마을이 조용해져서 좋아" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talkend = true;
		}
		//퀘스트4 대화
		if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"소닉이 걱정되요..." );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talkend = true;
		}
		//퀘스트5 대화
		if(CQuestMgr::GetInstance()->GetQuestNow() == 5 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"(자초지종을 설명한다)\n\n소닉이 사라졌다구요??\n용사님도 찾으러 가겠다니\n저도 찾으러 가 봐야 겠어요" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 5 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"저는 카우가 있던곳을 찾아볼께요!\n모험가님은 필드 동쪽 끝에서 찾아봐 주세요!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		//퀘스트5 대화
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"고갱님.. 아니 모험가님 많이 놀라셨죠? 저 아이작 이에요...!\n여기까지 오시느라 수고 많으셨습니다!\n단역인데 무려 60프레임이나 잡아먹는 제가 나온 이유는?" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"바로 게임을 마칠때가 됐기 때문이겠죠?!\n시연회 발표에 참가해 주셔서 감사합니다~! \n\n T  H  E    E  N  D");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
	}

	//렉트보이기
	//CRectMgr::GetInstance()->Render(rcTalk,RECT_ID_CLICK);
}

void CIsaac::Release(void)
{

}

CObj* CIsaac::Clone(void)
{
	return new CIsaac(*this);
}

void CIsaac::SwitchSwap(bool* bSwitch)
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