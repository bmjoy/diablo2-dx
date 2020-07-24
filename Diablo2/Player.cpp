#include "StdAfx.h"
#include "Player.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

#include "KeyMgr.h"
#include "Astar.h"

#include "ObjMgr.h"
#include "StateMgr.h"
#include "ScrollMgr.h"
#include "RectMgr.h"
#include "TextMgr.h"

#include "SoundMgr.h"
#include "RandomMgr.h"

//모션잡을때 PlayerRunToStand 에 항상 예외를 걸어야한다

CPlayer::CPlayer(void)
: m_fFrame(0.f)
, m_iMaxCnt(0)
, m_fRunTick(0.f)
, m_bClick(false)
{
}

CPlayer::CPlayer(const INFO& Info)
: CObj(Info)
, m_fFrame(0.f)
, m_iMaxCnt(0)
, m_fRunTick(0.f)
, m_bClick(false)
{

}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize( void )
{
	//타일받아오기
	m_vecTile = CObjMgr::GetInstance()->GetTileInfo();

	//위치,벡터
	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);//(256.f / 2.f, 256.f / 2.f, 0.0f);
	m_Info.vPos = D3DXVECTOR3(400.f, 300.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	
	
	//STATUS
	m_Status.iMaxHp = 500;
	m_Status.iMaxMana = 500;
	m_Status.iHp = 500;
	m_Status.iMana = 500;
	m_Status.Str = 10;
	m_Status.Int = 0;
	m_Status.Dex = 10;
	m_Status.Vit = 10;
	m_Status.Lv = 1;
	m_Status.iAtk = 30;
	m_Status.iDef = 10;
	m_iStateID = 0;
	m_fAngleNum = 11.25;
	m_Status.fAngle = 270.f;
	Now = 0; Goal = 0;
	
	//공격 RECT 초기화
	m_AtkRect.fSizeX = 0;
	m_AtkRect.fSizeY = 0;
	m_AtkRect.fX = 0;
	m_AtkRect.fY = 0;
	//걷지마
	m_bNotWalk = false;
	////유저 RECT 초기화
	//m_ObjRect.fSizeX
	//m_ObjRect.fSizeY
	//m_ObjRect.fX = m_Info.vPos.x;
	//m_ObjRect.fY = m
}

void CPlayer::Progress( void )
{

	D3DXMATRIX		matTrans;

	KeyInput();

	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	m_fRunTick += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	if(!m_BestList.empty())
	{		
		AStarMove();
	}	
	else
	{
		ZeroMemory(&m_Info.vDir, sizeof(m_Info.vDir));
	}

	if(m_fFrame > m_iMaxCnt)
	{
		//공격모션 끝나면 렉트를 지우기
		m_AtkRect.fSizeX =	0;
		m_AtkRect.fSizeY =	0;
		m_AtkRect.fX	=	m_Info.vPos.x;
		m_AtkRect.fY	=	m_Info.vPos.y;

		//모션들의 maxframe가 넘어가면 frame카운트를 0, 그리고 서있는자세로
		m_fFrame = 0.f;	 
		PlayerStand(m_Status.fAngle);
	}
	PlayerRunToStand();	

	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);

	m_Info.matWorld = matTrans;

}

void CPlayer::Render( void )
{	
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_PLAYER, m_iStateID, int(m_fFrame))
		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//공격 렉트 이미지로 보이기
	//CRectMgr::GetInstance()->Render(m_AtkRect,RECT_ID_ATK);
}

void CPlayer::KeyInput(void)
{
	if(PUSH_KEY(KEY_LBUTTON) && !m_bNotWalk ) //마우스 왼클릭
	{
		if(m_iStateID != OBJECT_STATEID_PLAYER_ATTACK1
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK2
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK3
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK4
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK5
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK6
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK7
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK8
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK9
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK10
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK11
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK12
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK13
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK14
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK15
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK16)
		{
			if (m_bClick)
			{
				return;
			}
			m_bClick = true;
			///포인터(골지점) 좌표 받아오는 용도
			POINT pt,Playerpt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd,&pt);
			//플레이어의 좌표
			Playerpt.x = long(m_Info.vPos.x);
			Playerpt.y = long(m_Info.vPos.y); 
			///
			for (size_t i = 0; i < m_vecTile.size(); ++i)
			{
				if(CollisionMtoT(i, pt))
				{
					m_fInfoX = CObjMgr::GetInstance()->GetTileInfo()[i]->iX;
					m_fInfoY = CObjMgr::GetInstance()->GetTileInfo()[i]->iY;
					Goal = i;
				}
				if(CollisionMtoT(i, Playerpt))
				{
					Now = i;
				}
			}
			m_BestList = CAStar::GetInstance()->AStarStart(Now, Goal);	
		}
	}
	else
	{
		m_bClick = false;
	}
	//if(PUSH_KEY(KEY_LBUTTON)) //마우스 왼클릭
	//{
	//	//AstarStart();     //Astar시작

	//	//방향벡터 구하자
	//	m_Info.vDir.x = pt.x - m_Info.vPos.x; 
	//	m_Info.vDir.y = pt.y - m_Info.vPos.y;

	//	//내적을 합시다
	//	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
	//	D3DXVec3Normalize(&m_Info.vLook, &m_Info.vLook);
	//	
	//	// 내가 가고싶은 장소에 대한 각도, 내적을 구해주는 함수.
	//	float m_fAngle = acosf(D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook));	

	//	//acos는 180도 넘어가면 삐꾸가 된다 그래서...
	//	if( pt.y > m_Info.vPos.y )
	//	{
	//		m_fAngle = 2 * D3DX_PI - m_fAngle;
	//	}

	//	m_Info.vPos.x += cosf(m_fAngle) * 0.5f;
	//	m_Info.vPos.y += -sinf(m_fAngle) * 0.5f;
	//}

	if(PUSH_KEY(KEY_SPACE))
	{
		//m_AtkRect.fX	=	m_Info.vPos.x	-	35;
		//m_AtkRect.fY	=	m_Info.vPos.y	-	25;

		PlayerAtk(m_Status.fAngle);
	}
}

bool CPlayer::CollisionMtoT(int iIndex, POINT ptMouse)
{


	int tilesizex = 160, tilesizey = 80;

	float	fGrad = (tilesizey / 2.f) / (tilesizex / 2.f);

	POINT		pt[4];
	// 왼쪽
	pt[0].x = long(m_vecTile[iIndex]->iX - tilesizex / 2);
	pt[0].y = long(m_vecTile[iIndex]->iY);

	// 위쪽
	pt[1].x = long(m_vecTile[iIndex]->iX);
	pt[1].y = long(m_vecTile[iIndex]->iY + tilesizey / 2);

	// 오른쪽
	pt[2].x = long(m_vecTile[iIndex]->iX + tilesizex / 2);
	pt[2].y = long(m_vecTile[iIndex]->iY);

	// 아래쪽
	pt[3].x = long(m_vecTile[iIndex]->iX);
	pt[3].y = long(m_vecTile[iIndex]->iY - tilesizey / 2);	

	float	b[4];

	b[0] = pt[0].y - fGrad * pt[0].x;
	b[1] = pt[1].y - -fGrad * pt[1].x;
	b[2] = pt[2].y - fGrad * pt[2].x;
	b[3] = pt[3].y - -fGrad * pt[3].x;

	if(ptMouse.y - fGrad * ptMouse.x - b[0] <= 0
		&& ptMouse.y - -fGrad * ptMouse.x - b[1] <= 0
		&& ptMouse.y - fGrad * ptMouse.x - b[2] > 0
		&& ptMouse.y - -fGrad * ptMouse.x - b[3] > 0)
	{
		return true;
	}
		return false;
}

void CPlayer::AStarMove(void)
{
	int		iIndex = m_BestList.front();
	D3DXVECTOR3 vDestPos = D3DXVECTOR3(m_vecTile[iIndex]->iX, m_vecTile[iIndex]->iY, 0.f);

	m_Info.vDir = vDestPos - m_Info.vPos;

	float fDistance = D3DXVec3Length(&m_Info.vDir);

	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
	D3DXVec3Normalize(&m_Info.vLook,&m_Info.vLook);

	if(fDistance < 20.0f)
	{
		m_BestList.pop_front();
	}
	m_Status.fAngle = acosf(D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook));	

	//acos는 180도 넘어가면 삐꾸가 된다 그래서...
	if( vDestPos.y > m_Info.vPos.y )
	{
		m_Status.fAngle = 2 * D3DX_PI - m_Status.fAngle; //라디안값
	}
	//각도에 따라 다른 텍스쳐를 쓴다
	m_Status.fAngle = D3DXToDegree(m_Status.fAngle);
	PlayerMove(m_Status.fAngle);

	//캐릭터는 백그라운드가 움직이는 형태로 움직인다

	/*m_Info.vPos += m_Info.vDir * 300.0f * CTimeMgr::GetInstance()->GetPixelPerSec();*/

	/*
	//이 소스는 파기. 작동은 잘 됨
	int		GoalIndex = m_BestList.front();

	POINT		Goalpt = {m_vecTile[GoalIndex]->iX, m_vecTile[GoalIndex]->iY};

	m_Info.vDir.x = Goalpt.x - m_Info.vPos.x;
	m_Info.vDir.y = Goalpt.y - m_Info.vPos.y;

	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
	D3DXVec3Normalize(&m_Info.vLook, &m_Info.vLook);
	
	float m_fAngle = acosf(D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook));	

	//acos는 180도 넘어가면 삐꾸가 된다 그래서...
	if( Goalpt.y > m_Info.vPos.y )
	{
		m_fAngle = 2 * D3DX_PI - m_fAngle;
	}

	m_Info.vPos.x += cosf(m_fAngle) * 1.0f;
	m_Info.vPos.y += -sinf(m_fAngle) * 1.0f;

	D3DXVECTOR3 temp;
	temp.x = m_Info.vPos.x - Goalpt.x;
	temp.y = m_Info.vPos.y - Goalpt.y;
	temp.z = 0;

	if(D3DXVec3Length(&temp) < 5 )
	{		
		m_BestList.pop_front();
		//if(m_BestList.empty())
		//{
		//	
		//}
	}
	*/
}

void CPlayer::Release( void )
{

}

CObj* CPlayer::Clone( void )
{
	return new CPlayer(*this);
}





void CPlayer::PlayerMove(float m_fAngle)
{
	if( m_fRunTick >3.f)
	{
		CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(4,7),0); //칼소리
		m_fRunTick = 0.f;
	}
	if(m_fAngle <= 270 + m_fAngleNum && m_fAngle > 270 - m_fAngleNum)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN1)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN1;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum && m_fAngle > 270 - m_fAngleNum * 3 )
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN2)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN2;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 3 && m_fAngle > 270 - m_fAngleNum * 5)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN3)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN3;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 5 && m_fAngle >270 - m_fAngleNum * 7 )
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN4)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN4;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 7 && m_fAngle > 270 - m_fAngleNum * 9)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN5)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN5;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 9 && m_fAngle > 270 - m_fAngleNum * 11)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN6)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN6;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 11 && m_fAngle > 270 - m_fAngleNum * 13)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN7)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN7;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 13 && m_fAngle > 270 - m_fAngleNum * 15)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN8)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN8;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 15 && m_fAngle > 270 - m_fAngleNum * 17)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN9)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN9;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 17 && m_fAngle > 270 - m_fAngleNum * 19)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN10)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN10;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 19 && m_fAngle > 270 - m_fAngleNum * 21)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN11)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN11;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 21 && m_fAngle > 270 - m_fAngleNum * 23)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN12)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN12;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 23 || m_fAngle > 360 - m_fAngleNum) //0도와 360도 겹치는 부분
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN13)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN13;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <=  360 - m_fAngleNum && m_fAngle >  360 - m_fAngleNum * 3)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN14)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN14;
		m_iMaxCnt = 8;
	}
	if(m_fAngle > 360 - m_fAngleNum * 3 && m_fAngle <= 360 - m_fAngleNum * 5)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN15)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN15;
		m_iMaxCnt = 8;
	}
	if(m_fAngle <= 360 - m_fAngleNum * 5 && m_fAngle > 360 - m_fAngleNum * 7)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_RUN16)
			return;

		m_iStateID = OBJECT_STATEID_PLAYER_RUN16;
		m_iMaxCnt = 8;
	}
}

void CPlayer::PlayerStand(float m_fAngle)
{
		if(m_fAngle <= 270 + m_fAngleNum && m_fAngle > 270 - m_fAngleNum)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND1)
				return;
			//m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND1;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum && m_fAngle > 270 - m_fAngleNum * 3 )
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND2)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND2;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 3 && m_fAngle > 270 - m_fAngleNum * 5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND3)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND3;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 5 && m_fAngle >270 - m_fAngleNum * 7 )
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND4)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND4;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 7 && m_fAngle > 270 - m_fAngleNum * 9)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND5)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND5;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 9 && m_fAngle > 270 - m_fAngleNum * 11)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND6)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND6;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 11 && m_fAngle > 270 - m_fAngleNum * 13)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND7)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND7;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 13 && m_fAngle > 270 - m_fAngleNum * 15)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND8)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND8;
			m_iMaxCnt = 8;
		}	
		if(m_fAngle <= 270 - m_fAngleNum * 15 && m_fAngle > 270 - m_fAngleNum * 17)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND9)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND9;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 17 && m_fAngle > 270 - m_fAngleNum * 19)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND10)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND10;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 19 && m_fAngle > 270 - m_fAngleNum * 21)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND11)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND11;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 21 && m_fAngle > 270 - m_fAngleNum * 23)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND12)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND12;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 270 - m_fAngleNum * 23 || m_fAngle > 360 - m_fAngleNum) //0도와 360도 겹치는 부분
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND13)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND13;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <=  360 - m_fAngleNum && m_fAngle >  360 - m_fAngleNum * 3)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND14)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND14;
			m_iMaxCnt = 8;
		}
		if(m_fAngle > 360 - m_fAngleNum * 3 && m_fAngle <= 360 - m_fAngleNum * 5)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND15)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND15;
			m_iMaxCnt = 8;
		}
		if(m_fAngle <= 360 - m_fAngleNum * 5 && m_fAngle > 360 - m_fAngleNum * 7)
		{
			if(m_iStateID == OBJECT_STATEID_PLAYER_STAND16)
				return;
		//	m_fFrame = 0.f;
			m_iStateID = OBJECT_STATEID_PLAYER_STAND16;
			m_iMaxCnt = 8;
		}		
}

void CPlayer::PlayerAtk(float m_fAngle)
{
	CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(8,13),0); //공격음성
	CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(20,25),0); //칼휘두르는소리

	//평타렉트 사이즈 == 20
	m_AtkRect.fSizeX = 30;
	m_AtkRect.fSizeY = 30;

	//각도별로 모션 다르게
	// 270도 위치부터 시계방향으로 돌아감
	if(m_fAngle <= 270 + m_fAngleNum && m_fAngle > 270 - m_fAngleNum)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK1)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x;
		m_AtkRect.fY = m_Info.vPos.y + 60;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK1;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum && m_fAngle > 270 - m_fAngleNum * 3 )
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK2)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 15;
		m_AtkRect.fY = m_Info.vPos.y + 45;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK2;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 3 && m_fAngle > 270 - m_fAngleNum * 5)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK3)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 30;
		m_AtkRect.fY = m_Info.vPos.y + 30;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK3;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 5 && m_fAngle >270 - m_fAngleNum * 7 )
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK4)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 45;
		m_AtkRect.fY = m_Info.vPos.y + 15;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK4;
		m_iMaxCnt = 18;
	}
	//180도 방향 바라보는 시점
	if(m_fAngle <= 270 - m_fAngleNum * 7 && m_fAngle > 270 - m_fAngleNum * 9) 
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK5)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 60;
		m_AtkRect.fY = m_Info.vPos.y;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK5;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 9 && m_fAngle > 270 - m_fAngleNum * 11)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK6)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 45;
		m_AtkRect.fY = m_Info.vPos.y - 15;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK6;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 11 && m_fAngle > 270 - m_fAngleNum * 13)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK7)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 30;
		m_AtkRect.fY = m_Info.vPos.y - 30;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK7;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 13 && m_fAngle > 270 - m_fAngleNum * 15)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK8)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 15;
		m_AtkRect.fY = m_Info.vPos.y - 45;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK8;
		m_iMaxCnt = 18;
	}	
	// 90도 바라보는 시점
	if(m_fAngle <= 270 - m_fAngleNum * 15 && m_fAngle > 270 - m_fAngleNum * 17)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK9)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x;
		m_AtkRect.fY = m_Info.vPos.y - 60;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK9;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 17 && m_fAngle > 270 - m_fAngleNum * 19)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK10)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 15;
		m_AtkRect.fY = m_Info.vPos.y - 45;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK10;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 19 && m_fAngle > 270 - m_fAngleNum * 21)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK11)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 30;
		m_AtkRect.fY = m_Info.vPos.y - 30;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK11;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 21 && m_fAngle > 270 - m_fAngleNum * 23)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK12)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 45;
		m_AtkRect.fY = m_Info.vPos.y - 15;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK12;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 270 - m_fAngleNum * 23 || m_fAngle > 360 - m_fAngleNum) //0도와 360도 겹치는 부분
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK13)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 60;
		m_AtkRect.fY = m_Info.vPos.y;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK13;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <=  360 - m_fAngleNum && m_fAngle >  360 - m_fAngleNum * 3)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK14)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 45;
		m_AtkRect.fY = m_Info.vPos.y + 15;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK14;
		m_iMaxCnt = 18;
	}
	if(m_fAngle > 360 - m_fAngleNum * 3 && m_fAngle <= 360 - m_fAngleNum * 5)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK15)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 30;
		m_AtkRect.fY = m_Info.vPos.y + 30;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK15;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 360 - m_fAngleNum * 5 && m_fAngle > 360 - m_fAngleNum * 7)
	{
		if(m_iStateID == OBJECT_STATEID_PLAYER_ATTACK16)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 15;
		m_AtkRect.fY = m_Info.vPos.y + 45;
		m_iStateID = OBJECT_STATEID_PLAYER_ATTACK16;
		m_iMaxCnt = 18;
	}		
}

void CPlayer::PlayerRunToStand( void )
{
	if(m_BestList.empty() && m_iStateID != OBJECT_STATEID_PLAYER_ATTACK1
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK2
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK3
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK4
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK5
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK6
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK7
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK8
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK9
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK10
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK11
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK12
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK13
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK14
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK15
		&& m_iStateID != OBJECT_STATEID_PLAYER_ATTACK16)
	{
			PlayerStand(m_Status.fAngle);		
	}
}
