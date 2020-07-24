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
	m_Info.vPos = D3DXVECTOR3(9000.f,1800.f, 0.f); //�ʱ���ġ(���� �ִ°�)
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	m_vTownPos = D3DXVECTOR3(1750.f,730.f, 0.f);

	//������Ʈ�� RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 2;
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

void CSonic::Progress(void)
{
	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	m_Info.vPos.x -= fX;
	m_Info.vPos.y -= fY;
	m_vTownPos.x -= fX;
	m_vTownPos.y -= fY;

	//�����ִ� �Ҵ� rect
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

	//��� ������ ����
	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	
	if(m_fFrame > m_iMaxCnt)
	{
			m_fFrame = 0.f;	 
	}

	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PtInRect(&GetObjRect(),MousePt))
	{	//�Ҵ��� Ŭ��������
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
				//����Ʈ7 ��ȭ(����)
				if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7 && CQuestMgr::GetInstance()->GetKillCount3() == 1  )
				{
					talk1 = false;
					talkend = false;
					CQuestMgr::GetInstance()->SetQuestNow(); //����Ʈ8
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
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

void CSonic::Render(void)
{
	//�����ִ°��� �ϳ�
	if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7)
	{
	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�
	m_Info.matWorld = m_Info.matTrans; //������Ŀ� ����
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SONIC, OBJECT_STATEID_SONIC_HELP, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	//��������� ������
	if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST8 || CQuestMgr::GetInstance()->GetQuestNow() == 9)
	{
		m_iMaxCnt = 4;
		//D3DXMatrixIdentity(&m_Info.matTrans);
		//D3DXMatrixIdentity(&m_Info.matWorld);
		D3DXMatrixTranslation(&m_TransTown,m_vTownPos.x, m_vTownPos.y, m_vTownPos.z); //���������� �̵�
		m_WorldTown = m_TransTown; //������Ŀ� ����
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldTown);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SONIC, OBJECT_STATEID_SONIC_NOMAL, int(m_fFrame))
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//��ȭâ render
	if(m_bSwitch)
	{
		D3DXMatrixTranslation(&m_TransShop,257,256,0);
		m_WorldShop = m_TransShop;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SONIC, OBJECT_STATEID_SONIC_TALK)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		//����Ʈ 7 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == QUEST_NOW_QUEST7 && CQuestMgr::GetInstance()->GetKillCount3() == 1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�����ּż� �����մϴ�!!\n���� �״��� �˾Ҿ��..\n�������� �ٽ� ������!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}

		//����Ʈ9 ��ȭ
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"���谡��! �����ּż� ���� �����ϴ�!\n\n�� ���� ���� ��������!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 9 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�׷��� �� ���� ��½�Ÿ��� ����� ������?");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
	}

	//��Ʈ���̱�
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