#include "StdAfx.h"
#include "Panel.h"

CPanel::CPanel(void)
{
}

CPanel::~CPanel(void)
{
}

void CPanel::Initialize(void)
{
	m_fTime = 0;
	//��ǥ
	m_Info.vPos.x = 0;
	m_Info.vPos.y =500;
	m_Info.vPos.z = 0;

	m_Info.vCenter = D3DXVECTOR3(0.f,0.f,0.f);
	D3DXMatrixTranslation(&m_Info.matTrans,m_Info.vPos.x ,m_Info.vPos.y,m_Info.vPos.z);
	m_Info.matWorld = m_Info.matTrans;

	D3DXMatrixTranslation(&m_matTransHp,m_Info.vPos.x + 28 ,m_Info.vPos.y + 8 ,m_Info.vPos.z);
	m_matWorldHp  = m_matTransHp;

	D3DXMatrixTranslation(&m_matTransMp,m_Info.vPos.x + 690 ,m_Info.vPos.y + 8 ,m_Info.vPos.z);
	m_matWorldMp  = m_matTransMp;

	//HP MP
	m_HpSizeX = 80.f; //���� RECT�� �� HP,MP �̹����� ���� ������
	m_HpSizeY = 80.f;
	m_MpSizeX = 80.f;
	m_MpSizeY = 80.f;
	m_ImgSizeY = 80.f;

	//�̴Ϲ� ��Ʈ����
	//����
	rcStat.fSizeX = 23;
	rcStat.fSizeY = 23;
	rcStat.fX = 346;
	rcStat.fY = 533;
	//�κ�
	rcInven.fSizeX = 23;
	rcInven.fSizeY = 23;
	rcInven.fX = 382;
	rcInven.fY = 533;
	//��ų
	rcSkill.fSizeX = 23;
	rcSkill.fSizeY = 23;
	rcSkill.fX = 416;
	rcSkill.fY = 533;
	//����Ʈ
	rcQuest.fSizeX = 23;
	rcQuest.fSizeY = 23;
	rcQuest.fX = 447;
	rcQuest.fY = 533;

	//����
	m_ShowHpRc.fSizeX = 35;
	m_ShowHpRc.fSizeY = 35;
	m_ShowHpRc.fX = 68;
	m_ShowHpRc.fY = 542;
	//������
	m_ShowMpRc.fSizeX = 35;
	m_ShowMpRc.fSizeY = 35;
	m_ShowMpRc.fX = 733;
	m_ShowMpRc.fY = 542;
	
}
void CPanel::Progress(void)
{
	//m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();
	m_PlayerStat = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->GetStat(); //���ݾ���
	
	//if(m_fTime > 1.f)
	//{
	//	 m_fTime = 0;
	//	 CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->SetHp(5);
	//	 CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->SetMana(5);
	//}

	m_fHp = float(m_PlayerStat.iHp);
	m_fMana = float(m_PlayerStat.iMana);
	m_fMaxHp = float(m_PlayerStat.iMaxHp);
	m_fMaxMana = float(m_PlayerStat.iMaxMana);

	m_HpSizeY = m_ImgSizeY * (m_fHp / m_fMaxHp );

	m_MpSizeY = m_ImgSizeY * (m_fMana /m_fMaxMana);
	
}

void CPanel::Render(void)
{
		//ȭ����ǥ �̱��
		POINT MousePt = CMouseMgr::GetMousePos();

		//D3DXMATRIX			matTrans;
		//D3DXMATRIX			matWorld;
		//D3DXMatrixIdentity(&matWorld);
		//RECT		rcFont = {0};
		//
		//TCHAR		szBuf1[128];
		//ZeroMemory(&szBuf1, sizeof(szBuf1));
		//D3DXMatrixTranslation(&matTrans,50,50,0);
		//matWorld = matTrans;
		//CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		//wsprintf(szBuf1, L"X:%d", MousePt.x);
		//CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), szBuf1, lstrlen(szBuf1), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		//
		//TCHAR		szBuf2[128];
		//ZeroMemory(&szBuf2, sizeof(szBuf2));
		//D3DXMatrixTranslation(&matTrans,150,50,0);
		//matWorld = matTrans;
		//CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		//wsprintf(szBuf2, L"Y:%d", MousePt.y);
		//CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), szBuf2, lstrlen(szBuf2), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		//1.�����г�
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PANEL, OBJECT_STATEID_PANEL_PANEL)
			, NULL, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//2.����
		SetRect(&m_HpRect,0,int(m_ImgSizeY - m_HpSizeY) ,int(m_HpSizeX),int(m_ImgSizeY)); //hp�� mp�ٸ� ���� �̹����κ��� �󸶸�ŭ�� �о������ rect�� ����
		//rect�� ���� �з� �ö󰡴� ��ŭ, pos�� ������ �����ش�
		D3DXMatrixTranslation(&m_matTransHp,m_Info.vPos.x + 28 , m_Info.vPos.y + (8 + m_ImgSizeY - m_HpSizeY)  ,m_Info.vPos.z);
		m_matWorldHp  = m_matTransHp;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorldHp);
		//�׸���
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PANEL, OBJECT_STATEID_PANEL_HP)
			, &m_HpRect, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//3.������
		SetRect(&m_MpRect,0,int(m_ImgSizeY - m_MpSizeY) ,int(m_MpSizeX),int(m_ImgSizeY)); //hp�� mp�ٸ� ���� �̹����κ��� �󸶸�ŭ�� �о������ rect�� ����
		//rect�� ���� �з� �ö󰡴� ��ŭ, pos�� ������ �����ش�
		D3DXMatrixTranslation(&m_matTransMp,m_Info.vPos.x + 690 , m_Info.vPos.y + (8 + m_ImgSizeY - m_MpSizeY)  ,m_Info.vPos.z);
		m_matWorldMp = m_matTransMp;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorldMp);
		//�׸���
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PANEL, OBJECT_STATEID_PANELE_MP)
			, &m_MpRect, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		//2_1 ����ǥ��
		if(PtInRect(&(GetClickRect(m_ShowHpRc)),MousePt))
		{
			TCHAR		szHp[128];
			ZeroMemory(&szHp, sizeof(szHp));
			wsprintf(szHp, L"����: %d / %d", m_PlayerStat.iHp, m_PlayerStat.iMaxHp);
			CTextMgr::GetInstance()->MakeText(szHp,20,500,0.6f,0.6f);
		}
		//3_1 ����ǥ��
		if(PtInRect(&(GetClickRect(m_ShowMpRc)),MousePt))
		{
			TCHAR		szMp[128];
			ZeroMemory(&szMp, sizeof(szMp));
			wsprintf(szMp, L"����: %d / %d", m_PlayerStat.iMana, m_PlayerStat.iMaxMana);
			CTextMgr::GetInstance()->MakeText(szMp,690,500,0.6f,0.6f);
		}

		//�̴Ϲ�
		//CRectMgr::GetInstance()->Render(rcSkill,RECT_ID_CLICK);
		//CRectMgr::GetInstance()->Render(rcQuest,RECT_ID_CLICK);
		//CRectMgr::GetInstance()->Render(rcInven,RECT_ID_CLICK);
		//CRectMgr::GetInstance()->Render(rcStat,RECT_ID_CLICK);

}

void CPanel::Release(void)
{

}

CObj* CPanel::Clone( void )
{
	return new CPanel(*this);
}
