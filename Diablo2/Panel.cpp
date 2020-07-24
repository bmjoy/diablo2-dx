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
	//좌표
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
	m_HpSizeX = 80.f; //위에 RECT에 들어갈 HP,MP 이미지의 실제 사이즈
	m_HpSizeY = 80.f;
	m_MpSizeX = 80.f;
	m_MpSizeY = 80.f;
	m_ImgSizeY = 80.f;

	//미니바 렉트지정
	//스텟
	rcStat.fSizeX = 23;
	rcStat.fSizeY = 23;
	rcStat.fX = 346;
	rcStat.fY = 533;
	//인벤
	rcInven.fSizeX = 23;
	rcInven.fSizeY = 23;
	rcInven.fX = 382;
	rcInven.fY = 533;
	//스킬
	rcSkill.fSizeX = 23;
	rcSkill.fSizeY = 23;
	rcSkill.fX = 416;
	rcSkill.fY = 533;
	//퀘스트
	rcQuest.fSizeX = 23;
	rcQuest.fSizeY = 23;
	rcQuest.fX = 447;
	rcQuest.fY = 533;

	//피통
	m_ShowHpRc.fSizeX = 35;
	m_ShowHpRc.fSizeY = 35;
	m_ShowHpRc.fX = 68;
	m_ShowHpRc.fY = 542;
	//마나통
	m_ShowMpRc.fSizeX = 35;
	m_ShowMpRc.fSizeY = 35;
	m_ShowMpRc.fX = 733;
	m_ShowMpRc.fY = 542;
	
}
void CPanel::Progress(void)
{
	//m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();
	m_PlayerStat = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)->GetStat(); //스텟얻어옴
	
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
		//화면좌표 뽑기용
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

		//1.메인패널
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PANEL, OBJECT_STATEID_PANEL_PANEL)
			, NULL, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//2.피통
		SetRect(&m_HpRect,0,int(m_ImgSizeY - m_HpSizeY) ,int(m_HpSizeX),int(m_ImgSizeY)); //hp나 mp바를 원본 이미지로부터 얼마만큼만 읽어들일지 rect로 지정
		//rect가 위로 밀려 올라가는 만큼, pos를 밑으로 내려준다
		D3DXMatrixTranslation(&m_matTransHp,m_Info.vPos.x + 28 , m_Info.vPos.y + (8 + m_ImgSizeY - m_HpSizeY)  ,m_Info.vPos.z);
		m_matWorldHp  = m_matTransHp;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorldHp);
		//그린다
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PANEL, OBJECT_STATEID_PANEL_HP)
			, &m_HpRect, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//3.마나통
		SetRect(&m_MpRect,0,int(m_ImgSizeY - m_MpSizeY) ,int(m_MpSizeX),int(m_ImgSizeY)); //hp나 mp바를 원본 이미지로부터 얼마만큼만 읽어들일지 rect로 지정
		//rect가 위로 밀려 올라가는 만큼, pos를 밑으로 내려준다
		D3DXMatrixTranslation(&m_matTransMp,m_Info.vPos.x + 690 , m_Info.vPos.y + (8 + m_ImgSizeY - m_MpSizeY)  ,m_Info.vPos.z);
		m_matWorldMp = m_matTransMp;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_matWorldMp);
		//그린다
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PANEL, OBJECT_STATEID_PANELE_MP)
			, &m_MpRect, &m_Info.vCenter , NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		//2_1 피통표시
		if(PtInRect(&(GetClickRect(m_ShowHpRc)),MousePt))
		{
			TCHAR		szHp[128];
			ZeroMemory(&szHp, sizeof(szHp));
			wsprintf(szHp, L"생명: %d / %d", m_PlayerStat.iHp, m_PlayerStat.iMaxHp);
			CTextMgr::GetInstance()->MakeText(szHp,20,500,0.6f,0.6f);
		}
		//3_1 마나표시
		if(PtInRect(&(GetClickRect(m_ShowMpRc)),MousePt))
		{
			TCHAR		szMp[128];
			ZeroMemory(&szMp, sizeof(szMp));
			wsprintf(szMp, L"마나: %d / %d", m_PlayerStat.iMana, m_PlayerStat.iMaxMana);
			CTextMgr::GetInstance()->MakeText(szMp,690,500,0.6f,0.6f);
		}

		//미니바
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
