#include "StdAfx.h"
#include "QuestMgr.h"

CQuestMgr::CQuestMgr(void)
: m_fTime(0.f), m_fAlertTime(0.f) //����Ʈ �˸�â �ߴ� �ð�
{
}

CQuestMgr::~CQuestMgr(void)
{
}

void CQuestMgr::Initialize(void)
{
	m_iQuestNow = 0; //����Ʈ ����(���൵)
	m_iKillCount1 = 0; //����Ʈ1 ų ī��Ʈ
	m_iKillCount2 = 0; //����Ʈ2 ų ī��Ʈ
	m_iKillCount3 = 0; //���� ų ī��Ʈ

	m_bSwitchAlert = false; //m_fAlertTime ������ ����ġ
	m_bTalkSwitch = true;

	m_bQ4Close	 = false; //�Ҵ� �Ź��� ã�Ҵ�! �˸� ����
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
	//�÷��̾� ��ȭâ �ѱ涧
	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	//ġƮŰ(�ӽ�)
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
	{	//��ȭâ Ŭ��������
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

//////////////////////����Ʈ �׺�(ȭ��ǥ)//////////////////
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //���
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //������
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(535); //�޸�������
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2634); //����
	//((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2613); //ī��

	//�÷��̾��� ��ġ
	m_vecPlayerPos = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->GetInfo().vPos;

	//����Ʈ���� �������� �ٸ��� ������
	if( m_iQuestNow == QUEST_NOW_QUEST0)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //������
	}
	if( m_iQuestNow == QUEST_NOW_QUEST1)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //������
	}
	if( m_iQuestNow == QUEST_NOW_QUEST2 && m_iKillCount1 != 5)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(535); //�޸�������
	}
	if( m_iQuestNow == QUEST_NOW_QUEST2 && m_iKillCount1 == 5)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //������
	}
	if( m_iQuestNow == QUEST_NOW_QUEST3 )
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //���
	}
	if( m_iQuestNow == QUEST_NOW_QUEST4 && m_iKillCount2 != 5 )
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2613); //ī��
	}
	if( m_iQuestNow == QUEST_NOW_QUEST4 && m_iKillCount2 == 5 )
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //���
	}
	if( m_iQuestNow == QUEST_NOW_QUEST5)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(970); //������
	}
	if( m_iQuestNow == QUEST_NOW_QUEST6)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2634); //����
	}
	if( m_iQuestNow == QUEST_NOW_QUEST7 && m_iKillCount3 == 0)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(2634); //����
	}
	if( m_iQuestNow == QUEST_NOW_QUEST7 && m_iKillCount3 == 1)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //���(����)
	}
	if( m_iQuestNow == QUEST_NOW_QUEST8)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //���(����)
	}	
	if( m_iQuestNow == QUEST_NOW_QUEST9)
	{
		m_vecDestPos = ((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->GetTilePos(1030); //���(����)
	}	

	m_vecDir  = m_vecDestPos - m_vecPlayerPos;
	m_fDistance = D3DXVec3Length(&m_vecDir);
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);

	m_fAngle = acosf(D3DXVec3Dot( &m_vecLook, &m_vecDir));
	if( m_vecDestPos.y < m_vecPlayerPos.y)
	{
		m_fAngle = 2 * D3DX_PI - m_fAngle;
	}

////////////////////////����Ʈ �˸�////////////////////////
	//���� �ټ����� ������� �Ҵ��� �Ź��� ã�Ҵٰ� �˸���
	if(m_iKillCount2 == 5 && m_bQ4Close == false )
	{
		m_bSwitchAlert = true;
	}
	//����Ʈ6 �Ҵ� ��ó�� ���� �߰��ߴٰ� ���
	if(m_fDistance < 500.f && m_bQ6Close == false && m_iQuestNow == QUEST_NOW_QUEST6 )
	{
		m_bSwitchAlert = true;
	}
	//����Ʈ8 -> 9�� �Ѿ�� ������ ���ư�����!
	if(m_fDistance < 500.f && m_bQ8Close == false && m_iQuestNow == QUEST_NOW_QUEST8 )
	{
		m_bSwitchAlert = true;
	}
	//����Ʈ �˸�â�� 3�ʸ� ���
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
	//����Ʈ �׺������(�˸�)
	D3DXMatrixTranslation(&m_TransQuestNavi,650,100,0);
	m_WorldQuestNavi = m_TransQuestNavi;
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldQuestNavi);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALRAM)
		, NULL, NULL, NULL, D3DCOLOR_ARGB(100, 255, 255, 255));
	
	//���� �˷��ִ� ȭ��ǥ
	D3DXMatrixTranslation(&m_TransArrow,720,330,0);
	D3DXMatrixRotationZ(&m_RotzArrow, m_fAngle);
	m_WorldArrow = m_RotzArrow * m_TransArrow;
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldArrow);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ARROW)
		, NULL, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//�Ÿ� (������ ����Ʈ �������� ������)
	TCHAR		szText[128];
	ZeroMemory(&szText, sizeof(szText));
	wsprintf(szText, L"�����Ÿ�\n%d m",int(m_fDistance/10) );
	CTextMgr::GetInstance()->MakeText(szText,710,370,0.7f,0.8f);

	if( m_iQuestNow == QUEST_NOW_QUEST1 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 1 \n\n���������� �̵��Ͽ� \n�����۰� ��ȭ�ϼ���" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST2 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 2 \n\n���� �ϵ������� ������ \n�޸� ������ (%d/5)",m_iKillCount1);
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
		if(m_iKillCount1 == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"������ ���ư���\n�����۰� ��ȭ�ϼ���!");
			CTextMgr::GetInstance()->MakeText(szText,650,150,0.7f,0.7f);
		}
	}
	if( m_iQuestNow == QUEST_NOW_QUEST3 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 3 \n\n������ ���� �ִ� \n���� ��ȭ�ϼ���!" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST4 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 4 \n\nī����� óġ�ϼ��� \nī�� (%d/5)",m_iKillCount2 );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
		if(m_iKillCount2 == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"������ ���ư���\n���� ��ȭ�ϼ���!!");
			CTextMgr::GetInstance()->MakeText(szText,650,150,0.7f,0.7f);
		}
	}
	if( m_iQuestNow == QUEST_NOW_QUEST5 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 5 \n\n�����ۿ��� �Ҵ��� \nã���� ���ٰ� \n�����ּ���" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST6 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 6\n      B O S S \n\n�ʵ� ���� ������\n �̵��ϼ���" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if(m_iQuestNow == QUEST_NOW_QUEST7)
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 7\n      B O S S \n\n������ ����\n���ǽ��並 óġ�ϼ���\n���ǽ��� (%d/1)",m_iKillCount3 );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
		if(m_iKillCount3 == 1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"���ǽ��並 \nóġ�߽��ϴ�!\n�Ҵ��� Ǯ���ּ���");
			CTextMgr::GetInstance()->MakeText(szText,650,200,0.7f,0.7f);
		}
	}
	if( m_iQuestNow == QUEST_NOW_QUEST8 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 8\n�Ҵ��� ������\n�����߽��ϴ�\n������ ���ư�����" );
		CTextMgr::GetInstance()->MakeText(szText,650,100,0.7f,0.7f);
	}
	if( m_iQuestNow == QUEST_NOW_QUEST9 )
	{
		TCHAR		szText[128];
		ZeroMemory(&szText, sizeof(szText));
		wsprintf(szText, L"     Q U E S T 9\n      E N D \n   �Ҵ��� ������\n   ���ƿԽ��ϴ�!\n   ����������\n   ��ȭ�� ����������!" );
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
		wsprintf(szText, L"��ƺ��2�� ���Ű��� ȯ���մϴ�\n ���������� �̵��Ͽ� �����۰� ��ȭ�ϼ���!" );
		CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
	}

	//����Ʈ4 �˸�
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
		wsprintf(szText, L"�Ҵ��� �Ź��� �߰��ߴ�!");
		CTextMgr::GetInstance()->MakeText(szText,265,60,0.8f,0.8f);
		m_bQ4Close = true;
	}
	
	//����Ʈ6 �˸�
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
		wsprintf(szText, L"�����ִ� �Ҵ��� �߰��ߴ�!");
		CTextMgr::GetInstance()->MakeText(szText,265,60,0.8f,0.8f);
		m_bQ6Close = true;
	}

	//����Ʈ8 �˸�
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
		wsprintf(szText, L"���� ������ ��ȭ�� ����������!");
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