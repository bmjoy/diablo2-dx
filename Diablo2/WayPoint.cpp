#include "StdAfx.h"
#include "WayPoint.h"
#include "SoundMgr.h"
//��ó�� ó���ؼ� act���� �ٸ����� ����
CWayPoint::CWayPoint(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
,GoAct1(false), GoAct2(false), GoAct3(false)
{
}

CWayPoint::~CWayPoint(void)
{
}

void CWayPoint::Initialize(void)
{
	m_Info.vCenter = D3DXVECTOR3(100.f,50.f,0.f);
	m_Info.vPos = D3DXVECTOR3(1100.f,800.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	//������Ʈ�� RECT
	m_ObjRect.fSizeX = 75;
	m_ObjRect.fSizeY = 75;
	//
	m_iMaxCnt = 8;
	m_fTime = 0;
	m_bSwitch = false;

	//������ ��ư rect
	rcQUIT.fSizeX = 30;
	rcQUIT.fSizeY = 30;
	rcQUIT.fX = 366;
	rcQUIT.fY = 469;

	rcACT1.fSizeX = 25;
	rcACT1.fSizeY = 25;
	rcACT1.fX = 105;
	rcACT1.fY = 140;

	rcACT2.fSizeX = 25;
	rcACT2.fSizeY = 25;
	rcACT2.fX = 105;
	rcACT2.fY = 175;

	rcACT3.fSizeX = 25;
	rcACT3.fSizeY = 25;
	rcACT3.fX = 105;
	rcACT3.fY = 210;
}

void CWayPoint::Progress(void)
{
	//��ũ��
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

	//Ŭ���ϸ� ��������Ʈ
	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();
	if(PtInRect(&GetObjRect(),MousePt))
	{
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				CSoundMgr::GetInstance()->SoundPlay(2,0);
				((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
				SwitchSwap(&m_bNotWalk);
				SwitchSwap(&m_bSwitch);
				m_fTime = 0;
			}
	}
	//m_bSwitch : �ش� Ŭ������ ������� â�� ������°�?
	//��������Ʈ ���������
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcQUIT),MousePt)) //������ ��ư ������
		{
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				CSoundMgr::GetInstance()->SoundPlay(2,0);
				SwitchSwap(&m_bSwitch);
				SwitchSwap(&m_bNotWalk);
				m_fTime = 0;
			}
		}
		//��Ʈ �ѱ���� stage.cpp���� �Ѱܾ���
		//act1
		if(PtInRect(&GetClickRect(rcACT1),MousePt))
		{
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				GoAct1 = true;
			}
		}
		//act2
		if(PtInRect(&GetClickRect(rcACT2),MousePt))
		{
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				GoAct2 = true;
			}
		}
		//act3
		if(PtInRect(&GetClickRect(rcACT3),MousePt))
		{
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				//GoAct3 = true;
			}
		}
	}
}

void CWayPoint::Render(void)
{

	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�
	m_Info.matWorld = m_Info.matTrans; //������Ŀ� ����
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_WAYPOINT, OBJECT_STATEID_WAYPOINT_WAYPOINT, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	if(m_bSwitch)
	{
		D3DXMatrixTranslation(&m_TransShop,100,50,0);
		m_WorldShop = m_TransShop;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_WAYPOINT, OBJECT_STATEID_WAYPOINT_MENU)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//��Ʈ���̱�
	//CRectMgr::GetInstance()->Render(m_ObjRect,RECT_ID_CLICK);
	//CRectMgr::GetInstance()->Render(rcACT1,RECT_ID_CLICK);
	//CRectMgr::GetInstance()->Render(rcACT2,RECT_ID_CLICK);
	//CRectMgr::GetInstance()->Render(rcACT3,RECT_ID_CLICK);
}

void CWayPoint::Release(void)
{

}

CObj* CWayPoint::Clone(void)
{
	return new CWayPoint(*this);
}

void CWayPoint::SwitchSwap(bool* bSwitch)
{
	if(*bSwitch)
	{
		*bSwitch = false;
	}
	else
	{
		*bSwitch = true;
	}

	//return bSwitch;
}