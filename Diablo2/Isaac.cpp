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

	//������Ʈ�� RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 10;
	m_fTime = 0;
	m_bSwitch = false;

	//��ȭâ
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

	//��� ������ ����
	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	
	if(m_fFrame > m_iMaxCnt)
	{
			m_fFrame = 0.f;	 
	}

	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PtInRect(&GetObjRect(),MousePt))
	{	//�������� Ŭ��������
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				if( m_bNotWalk == false)
				{
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					SwitchSwap(&m_bNotWalk);
				}
				talk1 = true;
				SwitchSwap(&m_bSwitch); //��ȭâ�� ����
				m_fTime = 0;
			}
	}

	//��ȭâ ���ִ� ��Ȳ
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcTalk),MousePt)) 
		{	//��ȭâ�� ������
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				//����Ʈ1 ��ȭ
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

				//����Ʈ2 ��ȭ
				//����Ʈ���϶�
				if( CQuestMgr::GetInstance()->GetQuestNow() == 2 && CQuestMgr::GetInstance()->GetKillCount1() != 5 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//����Ʈ�� ��������
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
				
				//����Ʈ3 ��ȭ
				if( CQuestMgr::GetInstance()->GetQuestNow() == 3 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//����Ʈ4 ��ȭ
				if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5  )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//����Ʈ5 ��ȭ 
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
					CQuestMgr::GetInstance()->SetQuestNow(); //�� 6����
					m_fTime = 0;
				}
				//����Ʈ9 ��ȭ 
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
				//��� ��ȭ�� ������
				if( m_bNotWalk == true && talkend == true)
				{
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
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
		D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�
		m_Info.matWorld = m_Info.matTrans; //������Ŀ� ����
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
		D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�
		m_Info.matWorld = m_Info.matTrans; //������Ŀ� ����
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
		//����Ʈ1 ��ȭ textrender
		if(CQuestMgr::GetInstance()->GetQuestNow() == 1 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�ȳ��ϼ��� ���� �������̿��� �ݰ����ϴ�\n\n����� �����ϴ� Ȥ�� ���谡 �̽Ű���?" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 1 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�ֱ� �޸� ��������� �������� ���ͼ� �����̿���\n�ʵ� �ϵ��� ���� �ִ� �޸� ������ �������� ���ż�\n������ ���ֽø� ���� ����ſ���!\n����� ������ ���� ������ ����������");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}

		//����Ʈ2 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == 2 && CQuestMgr::GetInstance()->GetKillCount1() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�޸� ��������� ȥ���ּ��� �̤�" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}

		if(CQuestMgr::GetInstance()->GetQuestNow() == 2 && talk1 && CQuestMgr::GetInstance()->GetKillCount1() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�����ϴ� ���谡��!\n���п� �������� �޸����� ������ �ʰ� �ƾ��!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 2 && !talk1 && CQuestMgr::GetInstance()->GetKillCount1() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"��! ���谡��\n�� ���� ���ִ� ������ ���谡���� ã����\n� ã�ư� ������!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talk2 = false;
		}
		//����Ʈ3 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == 3 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"������ ���������� ����" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talkend = true;
		}
		//����Ʈ4 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�Ҵ��� �����ǿ�..." );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talkend = true;
		}
		//����Ʈ5 ��ȭ
		if(CQuestMgr::GetInstance()->GetQuestNow() == 5 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"(���������� �����Ѵ�)\n\n�Ҵ��� ������ٱ���??\n���Ե� ã���� ���ڴٴ�\n���� ã���� �� ���� �ھ��" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 5 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"���� ī�찡 �ִ����� ã�ƺ�����!\n���谡���� �ʵ� ���� ������ ã�ƺ� �ּ���!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		//����Ʈ5 ��ȭ
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"����.. �ƴ� ���谡�� ���� ������? �� ������ �̿���...!\n������� ���ô��� ���� �����̽��ϴ�!\n�ܿ��ε� ���� 60�������̳� ��ƸԴ� ���� ���� ������?" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�ٷ� ������ ��ĥ���� �Ʊ� �����̰���?!\n�ÿ�ȸ ��ǥ�� ������ �ּż� �����մϴ�~! \n\n T  H  E    E  N  D");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
	}

	//��Ʈ���̱�
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