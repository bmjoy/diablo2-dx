#include "StdAfx.h"
#include "Yuusha.h"
#include "SoundMgr.h"
//ACT2 �縷���� �ظŴ� ����
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

	//������Ʈ�� RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 7;
	m_fTime = 0;
	m_bSwitch = false;

	//����Ʈâ
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

	//��� ������ ����
	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	
	if(m_fFrame > m_iMaxCnt)
	{
			m_fFrame = 0.f;	 
	}

	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PtInRect(&GetObjRect(),MousePt))
	{	//��縦 Ŭ��������
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				if( m_bNotWalk == false)
				{
					CSoundMgr::GetInstance()->SoundPlay(28,0);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					SwitchSwap(&m_bNotWalk);
				}
				talk1 = true;
				SwitchSwap(&m_bSwitch); //��ȭâ�� ����
				m_fTime = 0;
			}
	}

	//��ȭâ
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcTalk),MousePt)) 
		{	//��ȭâ�� ������
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{	
				//����Ʈ3 ��ȭ 
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
					CQuestMgr::GetInstance()->SetQuestNow(); //�� 4��
					m_fTime = 0;
				}
				//����Ʈ4 ��ȭ
				//����Ʈ���϶�
				if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//����Ʈ�� ��������
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
				//����Ʈ 5�϶�
				if( CQuestMgr::GetInstance()->GetQuestNow() == 5 && CQuestMgr::GetInstance()->GetKillCount3() != 1 )
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//����Ʈ 9�϶�
				if( CQuestMgr::GetInstance()->GetQuestNow() == 9)
				{
					talk1 = false;
					talkend = false;
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					m_fTime = 0;
				}
				//��� ��ȭ�� ������
				if( m_bNotWalk == true && talkend == true)
				{
					talkend = false;
					SwitchSwap(&m_bNotWalk);
					((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
					SwitchSwap(&m_bSwitch); //��ȭâ ����
					m_fTime = 0;
				}
			}
		}
	}
}

void CYuusha::Render(void)
{

	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�
	m_Info.matWorld = m_Info.matTrans; //������Ŀ� ����
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

		//����Ʈ3 ��ȭ textrender
		if(CQuestMgr::GetInstance()->GetQuestNow() == 3 && talk1)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"��, �����ڴ� �� ���̾��!\n\n���� �����ڴ��� ã�Ҵ� ������\n�� ģ�� �Ҵ��� �����ٰ� ���ƿ��� �ʰ� �־��\n�� �� ã�ƺ� �ֽ� �� ��������?" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 3 && talk2)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�Ҵ��� ī����� �ִ°����� �����ڴٰ� ���߾����\nī����� ���� �� �����ʿ� �־��!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		//����Ʈ4 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == 4 && CQuestMgr::GetInstance()->GetKillCount2() != 5 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�Ҵо� ��𰬴�..." );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 4 && talk1 && CQuestMgr::GetInstance()->GetKillCount2() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�ƴ�? �װ���..\n\n�Ҵ��� �Ź�??\n�Ҵп��� ���� �� �������� ������� Ʋ�������!!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		if(CQuestMgr::GetInstance()->GetQuestNow() == 4 && !talk1 && CQuestMgr::GetInstance()->GetKillCount2() == 5)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"���� �Ҵ��� ã���� ���߰ھ��!\n�����ۿ��Ե� �˷��ּ���!");
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
			talk2 = false;
		}
		//����Ʈ5 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == 5 && CQuestMgr::GetInstance()->GetKillCount3() != 1 )
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�� ����ϰڽ��ϴ�!" );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
		//����Ʈ9 ��ȭ
		if( CQuestMgr::GetInstance()->GetQuestNow() == 9)
		{
			TCHAR		szText[128];
			ZeroMemory(&szText, sizeof(szText));
			wsprintf(szText, L"�Ҵ��� �����ּż� ���� ������!\n�׷��� �������� ��𰡰� ��½�̴� ����� �ֳ׿�\n�� �����Խø�..." );
			CTextMgr::GetInstance()->MakeText(szText,20,50,1.f,1.f);
		}
	}

	//��Ʈ���̱�
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