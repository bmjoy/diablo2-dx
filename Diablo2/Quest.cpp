#include "StdAfx.h"
#include "Quest.h"
#include "SoundMgr.h"

CQuest::CQuest(void)
{
}

CQuest::~CQuest(void)
{
}

void CQuest::Initialize(void)
{
	//��ǥ����
	m_Info.vPos.x = 0;
	m_Info.vPos.y =0;
	m_Info.vPos.z = 0;

	m_Info.vCenter = D3DXVECTOR3(0.f,0.f,0.f);
	D3DXMatrixTranslation(&m_Info.matTrans,m_Info.vPos.x ,m_Info.vPos.y,m_Info.vPos.z);
	m_Info.matWorld = m_Info.matTrans;
	
	//â���� 
	m_fTime = 0;
	m_bSwitch = false;

	//����Ʈ1 Ŭ��
	Q1.fSizeX = 50;
	Q1.fSizeY = 50;
	Q1.fX = 134;
	Q1.fY = 153;
	//����Ʈ2 Ŭ��
	Q2.fSizeX = 50;
	Q2.fSizeY = 50;
	Q2.fX = 238;
	Q2.fY = 155;
	//����Ʈ3 Ŭ��
	Q3.fSizeX = 50;
	Q3.fSizeY = 50;
	Q3.fX = 342;
	Q3.fY = 153;
	//���� Ŭ��

	//����Ʈ ��Ʈ �����ֱ�
	ShowQ1Note = false;
	ShowQ2Note = false;
	ShowQ3Note = false;

}

void CQuest::Progress(void)
{
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();

	if(PUSH_KEY(KEY_Q) && m_fTime > 0.3f)
	{
		CSoundMgr::GetInstance()->SoundPlay(2,0);
		m_fTime = 0;
		//���� ������
		m_bNotWalk = SwitchSwap(m_bNotWalk);
		//����â �Ѱ� ����
		m_bSwitch = SwitchSwap(m_bSwitch);
	}
}

void CQuest::Render(void)
{	
	CQuestMgr::GetInstance()->Render();

	if( m_bSwitch )
	{
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_QUEST, OBJECT_STATEID_QUEST_QUEST)
			, NULL, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		POINT MousePt = CMouseMgr::GetMousePos();

		//����Ʈ1 ����
		if( PtInRect(&(GetClickRect(Q1)),MousePt))
		{
			if( PUSH_KEY(KEY_LBUTTON))
			{
				ShowQ1Note = true;
				ShowQ2Note = false;
				ShowQ3Note = false;
			}
		}	
		if(ShowQ1Note)
		{
			TCHAR		szStr[128];
			ZeroMemory(&szStr, sizeof(szStr));
			wsprintf(szStr, L"����Ʈ1 �����Դϴ�\n"L"������");
			MakeText(szStr,105,331);		
		}

		//����Ʈ2 ����
		if( PtInRect(&(GetClickRect(Q2)),MousePt))
		{
			if( PUSH_KEY(KEY_LBUTTON))
			{
				ShowQ1Note = false;
				ShowQ2Note = true;
				ShowQ3Note = false;
			}
		}	
		if(ShowQ2Note)
		{
			TCHAR		szStr[128];
			ZeroMemory(&szStr, sizeof(szStr));
			wsprintf(szStr, L"����Ʈ2 �����Դϴ�\n"L"������");
			MakeText(szStr,105,331);		
		}

		//����Ʈ3 ����
		if( PtInRect(&(GetClickRect(Q3)),MousePt))
		{
			if( PUSH_KEY(KEY_LBUTTON))
			{
				ShowQ1Note = false;
				ShowQ2Note = false;
				ShowQ3Note = true;
			}
		}	
		if(ShowQ3Note)
		{
			TCHAR		szStr[128];
			ZeroMemory(&szStr, sizeof(szStr));
			wsprintf(szStr, L"����Ʈ3 �����Դϴ�\n"L"������");
			MakeText(szStr,105,331);		
		}
		//CRectMgr::GetInstance()->Render(Q1,RECT_ID_CLICK);
		//CRectMgr::GetInstance()->Render(Q2,RECT_ID_CLICK);
		//CRectMgr::GetInstance()->Render(Q3,RECT_ID_CLICK);
		//CRectMgr::GetInstance()->Render(EXIT,RECT_ID_CLICK);
	}
}


void CQuest::Release(void)
{

}

CObj* CQuest::Clone( void )
{
	return new CQuest(*this);
}

void CQuest::MakeText(PTCHAR _pText, float _fX, float _fY)
{
		RECT		rcFont = {0};
		D3DXMATRIX			matTrans;
		D3DXMATRIX			matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matTrans,_fX,_fY,0);
		matWorld = matTrans;
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);		
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), _pText, lstrlen(_pText), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}