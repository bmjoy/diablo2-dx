#include "StdAfx.h"
#include "PshopNpc.h"
#include "SoundMgr.h"

CPshopNpc::CPshopNpc(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
{
}

CPshopNpc::~CPshopNpc(void)
{
}

void CPshopNpc::Initialize(void)
{
	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);
	m_Info.vPos = D3DXVECTOR3(2700.f,250.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	//������Ʈ�� RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 12;
	m_fTime = 0;
	m_bSwitch = false;

	//������ ��ư rect
	rcQUIT.fSizeX = 30;
	rcQUIT.fSizeY = 30;
	rcQUIT.fX = 366;
	rcQUIT.fY = 469;
}

void CPshopNpc::Progress(void)
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

	//Ŭ���ϸ� ���� ����
	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();
	if(PtInRect(&GetObjRect(),MousePt))
	{
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f) //�κ��� ���� ����
			{
				if( m_bNotWalk == false)
				{
					CSoundMgr::GetInstance()->SoundPlay(26,0);
					SwitchSwap(&m_bNotWalk);
				}
				((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
				SwitchSwap(&m_bSwitch);
				CObjMgr::GetInstance()->GetObj(OBJECT_INVEN,0)->SetSwitch(true);
				m_fTime = 0;
			}
	}

	//����â ���������
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcQUIT),MousePt)) //������ ��ư ������
		{
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				if( m_bNotWalk == true)
				{
					SwitchSwap(&m_bNotWalk);
				}
				SwitchSwap(&m_bSwitch);
				CObjMgr::GetInstance()->GetObj(OBJECT_INVEN,0)->SetSwitch(false);
				m_fTime = 0;
			}
		}
	}
}

void CPshopNpc::Render(void)
{

	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�
	m_Info.matWorld = m_Info.matTrans; //������Ŀ� ����
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PSHOPNPC, OBJECT_STATEID_PSHOPNPC_PSHOPNPC, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	if(m_bSwitch)
	{
		D3DXMatrixTranslation(&m_TransShop,257,256,0);
		m_WorldShop = m_TransShop;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PSHOPNPC, OBJECT_STATEID_PSHOPNPC_PSHOPLIST)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//��Ʈ���̱�
	//CRectMgr::GetInstance()->Render(rcQUIT,RECT_ID_CLICK);
}

void CPshopNpc::Release(void)
{

}

CObj* CPshopNpc::Clone(void)
{
	return new CPshopNpc(*this);
}

void CPshopNpc::SwitchSwap(bool* bSwitch)
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