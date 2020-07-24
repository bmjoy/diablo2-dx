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

//��������� PlayerRunToStand �� �׻� ���ܸ� �ɾ���Ѵ�

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
	//Ÿ�Ϲ޾ƿ���
	m_vecTile = CObjMgr::GetInstance()->GetTileInfo();

	//��ġ,����
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
	
	//���� RECT �ʱ�ȭ
	m_AtkRect.fSizeX = 0;
	m_AtkRect.fSizeY = 0;
	m_AtkRect.fX = 0;
	m_AtkRect.fY = 0;
	//������
	m_bNotWalk = false;
	////���� RECT �ʱ�ȭ
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
		//���ݸ�� ������ ��Ʈ�� �����
		m_AtkRect.fSizeX =	0;
		m_AtkRect.fSizeY =	0;
		m_AtkRect.fX	=	m_Info.vPos.x;
		m_AtkRect.fY	=	m_Info.vPos.y;

		//��ǵ��� maxframe�� �Ѿ�� frameī��Ʈ�� 0, �׸��� ���ִ��ڼ���
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

	//���� ��Ʈ �̹����� ���̱�
	//CRectMgr::GetInstance()->Render(m_AtkRect,RECT_ID_ATK);
}

void CPlayer::KeyInput(void)
{
	if(PUSH_KEY(KEY_LBUTTON) && !m_bNotWalk ) //���콺 ��Ŭ��
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
			///������(������) ��ǥ �޾ƿ��� �뵵
			POINT pt,Playerpt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd,&pt);
			//�÷��̾��� ��ǥ
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
	//if(PUSH_KEY(KEY_LBUTTON)) //���콺 ��Ŭ��
	//{
	//	//AstarStart();     //Astar����

	//	//���⺤�� ������
	//	m_Info.vDir.x = pt.x - m_Info.vPos.x; 
	//	m_Info.vDir.y = pt.y - m_Info.vPos.y;

	//	//������ �սô�
	//	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
	//	D3DXVec3Normalize(&m_Info.vLook, &m_Info.vLook);
	//	
	//	// ���� ������� ��ҿ� ���� ����, ������ �����ִ� �Լ�.
	//	float m_fAngle = acosf(D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook));	

	//	//acos�� 180�� �Ѿ�� �ٰ߲� �ȴ� �׷���...
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
	// ����
	pt[0].x = long(m_vecTile[iIndex]->iX - tilesizex / 2);
	pt[0].y = long(m_vecTile[iIndex]->iY);

	// ����
	pt[1].x = long(m_vecTile[iIndex]->iX);
	pt[1].y = long(m_vecTile[iIndex]->iY + tilesizey / 2);

	// ������
	pt[2].x = long(m_vecTile[iIndex]->iX + tilesizex / 2);
	pt[2].y = long(m_vecTile[iIndex]->iY);

	// �Ʒ���
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

	//acos�� 180�� �Ѿ�� �ٰ߲� �ȴ� �׷���...
	if( vDestPos.y > m_Info.vPos.y )
	{
		m_Status.fAngle = 2 * D3DX_PI - m_Status.fAngle; //���Ȱ�
	}
	//������ ���� �ٸ� �ؽ��ĸ� ����
	m_Status.fAngle = D3DXToDegree(m_Status.fAngle);
	PlayerMove(m_Status.fAngle);

	//ĳ���ʹ� ��׶��尡 �����̴� ���·� �����δ�

	/*m_Info.vPos += m_Info.vDir * 300.0f * CTimeMgr::GetInstance()->GetPixelPerSec();*/

	/*
	//�� �ҽ��� �ı�. �۵��� �� ��
	int		GoalIndex = m_BestList.front();

	POINT		Goalpt = {m_vecTile[GoalIndex]->iX, m_vecTile[GoalIndex]->iY};

	m_Info.vDir.x = Goalpt.x - m_Info.vPos.x;
	m_Info.vDir.y = Goalpt.y - m_Info.vPos.y;

	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
	D3DXVec3Normalize(&m_Info.vLook, &m_Info.vLook);
	
	float m_fAngle = acosf(D3DXVec3Dot(&m_Info.vDir, &m_Info.vLook));	

	//acos�� 180�� �Ѿ�� �ٰ߲� �ȴ� �׷���...
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
		CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(4,7),0); //Į�Ҹ�
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
	if(m_fAngle <= 270 - m_fAngleNum * 23 || m_fAngle > 360 - m_fAngleNum) //0���� 360�� ��ġ�� �κ�
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
		if(m_fAngle <= 270 - m_fAngleNum * 23 || m_fAngle > 360 - m_fAngleNum) //0���� 360�� ��ġ�� �κ�
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
	CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(8,13),0); //��������
	CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(20,25),0); //Į�ֵθ��¼Ҹ�

	//��Ÿ��Ʈ ������ == 20
	m_AtkRect.fSizeX = 30;
	m_AtkRect.fSizeY = 30;

	//�������� ��� �ٸ���
	// 270�� ��ġ���� �ð�������� ���ư�
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
	//180�� ���� �ٶ󺸴� ����
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
	// 90�� �ٶ󺸴� ����
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
	if(m_fAngle <= 270 - m_fAngleNum * 23 || m_fAngle > 360 - m_fAngleNum) //0���� 360�� ��ġ�� �κ�
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
