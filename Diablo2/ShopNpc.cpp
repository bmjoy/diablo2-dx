#include "StdAfx.h"
#include "ShopNpc.h"
#include "SoundMgr.h"

CShopNpc::CShopNpc(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
{
}

CShopNpc::~CShopNpc(void)
{
}

void CShopNpc::Initialize(void)
{
	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);
	m_Info.vPos = D3DXVECTOR3(1100.f,200.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	//오브젝트의 RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	//
	m_iMaxCnt = 13;
	m_fTime = 0;
	m_bSwitch = false;

	//나가기 버튼 rect
	rcQUIT.fSizeX = 30;
	rcQUIT.fSizeY = 30;
	rcQUIT.fX = 366;
	rcQUIT.fY = 469;
}

void CShopNpc::Progress(void)
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

	//클릭하면 상점 띄우기
	POINT MousePt = CMouseMgr::GetMousePos();
	m_fTime += CTimeMgr::GetInstance()->GetPixelPerSec();
	if(PtInRect(&GetObjRect(),MousePt))
	{
		if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f) //인벤도 같이 띄운다
			{
				CSoundMgr::GetInstance()->SoundPlay(27,0);
				((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
				SwitchSwap(&m_bNotWalk);
				SwitchSwap(&m_bSwitch);
				CObjMgr::GetInstance()->GetObj(OBJECT_INVEN,0)->SetSwitch(true);
				m_fTime = 0;
			}
	}

	//상점창 띄워졌을때
	if(m_bSwitch)
	{
		if(PtInRect(&GetClickRect(rcQUIT),MousePt)) //나가기 버튼 누르면
		{
			if( PUSH_KEY(KEY_LBUTTON) && m_fTime > 0.3f)
			{
				SwitchSwap(&m_bSwitch);
				CObjMgr::GetInstance()->GetObj(OBJECT_INVEN,0)->SetSwitch(false);
				m_fTime = 0;
				SwitchSwap(&m_bNotWalk);
				((CPlayer*)(CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0)))->ClearBestList();
			}
		}
	}
}

void CShopNpc::Render(void)
{

	D3DXMatrixTranslation(&m_Info.matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //이동시키는 함수
	m_Info.matWorld = m_Info.matTrans; //월드행렬에 적용
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SHOPNPC, OBJECT_STATEID_SHOPNPC_SHOPNPC, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	if(m_bSwitch)
	{
		D3DXMatrixTranslation(&m_TransShop,257,256,0);
		m_WorldShop = m_TransShop;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_WorldShop);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_SHOPNPC, OBJECT_STATEID_SHOPNPC_SHOPLIST)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	//렉트보이기
	//CRectMgr::GetInstance()->Render(rcQUIT,RECT_ID_CLICK);
}

void CShopNpc::Release(void)
{

}

CObj* CShopNpc::Clone(void)
{
	return new CShopNpc(*this);
}

void CShopNpc::SwitchSwap(bool* bSwitch)
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