#include "StdAfx.h"
#include "Boss1.h"
#include "SoundMgr.h"

CBoss1::CBoss1(void)
:m_fFrame(0.f)
,m_iMaxCnt(0)
,m_fDieTime(0.f)
,m_fDieEndTime(0.f)
,DieTimeCount(false)
,DieCheck(false)
,m_fAstarTick(0.f)
{
}

CBoss1::~CBoss1(void)
{
}

void CBoss1::Initialize( void )
{
	m_vecTile = CObjMgr::GetInstance()->GetTileInfo();
	m_pPlayer = CObjMgr::GetInstance()->GetObj(OBJECT_PLAYER,0);

	m_Info.vCenter = D3DXVECTOR3(256.f,256.f,0.f);
	//m_Info.vPos = D3DXVECTOR3(0.f,0.f,0.f);
	m_Info.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);	

	//����
	m_Status.iMaxHp = 500;
	m_Status.iMaxMana = 500;
	m_Status.iHp = 50;
	m_Status.iMana = 500;
	m_Status.iAtk = 5;
	m_Status.iDef = 1;

	//���
	m_iStateID = 1;
	m_Status.fAngle = 270.f;
	m_Status.Now = 0;
	m_Status.Goal = 0;
	m_Status.fAngleNum = 11.25;

	//���� RECT �ʱ�ȭ
	m_AtkRect.fSizeX = 0;
	m_AtkRect.fSizeY = 0;
	m_AtkRect.fX = 0;
	m_AtkRect.fY = 0;

	//������Ʈ�� RECT
	m_ObjRect.fSizeX = 15;
	m_ObjRect.fSizeY = 15;
	m_ObjRect.fX = 0;
	m_ObjRect.fY = 0;

	m_fDealTime = 0.f;
}

void CBoss1::Progress( void )
{
	//��ũ��
	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();

	m_Info.vPos.x -= fX;
	m_Info.vPos.y -= fY;

	//��� ������ ����
	m_fFrame += m_iMaxCnt * CTimeMgr::GetInstance()->GetPixelPerSec();
	//�� ������ �ð�
	m_fDealTime	+=	 CTimeMgr::GetInstance()->GetPixelPerSec();

	if(m_fFrame > m_iMaxCnt)
	{
		//���ݸ�� ������ ��Ʈ�� �����
		m_AtkRect.fSizeX =	0;
		m_AtkRect.fSizeY =	0;
		m_AtkRect.fX	=	m_Info.vPos.x;
		m_AtkRect.fY	=	m_Info.vPos.y;

		m_fFrame = 0.f;
		if(m_iStateID != OBJECT_STATEID_BOSS_DIE1 && m_iStateID != OBJECT_STATEID_BOSS_DIE2)
		{
			Stand(m_Status.fAngle);
		}
	}
	/////���� ���� ����//////
	DistanceChk(); //�������� �Ÿ� üũ
	Pattern();
	RunToStand();	
	
	//�״� ��� �����ϸ� 1�ʰ� ������
	if( DieTimeCount )
	{
		CSoundMgr::GetInstance()->SoundPlay(40,0); //�״¼Ҹ�
		m_fDieTime +=  CTimeMgr::GetInstance()->GetPixelPerSec();
	}
	//bestlist�� ������� �������� astarmove ���
	if(!m_BestList.empty())
	{
		AStarMove();
	}
	else
	{
		ZeroMemory(&m_Info.vDir, sizeof(m_Info.vDir));
	}

	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z); //�̵���Ű�� �Լ�

	m_Info.matWorld = matTrans; //������Ŀ� ����

	m_ObjRect.fX	=	m_Info.vPos.x;
	m_ObjRect.fY	=	m_Info.vPos.y;
}

void CBoss1::Render( void )
{
	//�״¸�� �����ְ���
	if( m_fDieTime > 2.3f )
	{
		m_iStateID = OBJECT_STATEID_BOSS_DIE2;
		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BOSS, OBJECT_STATEID_BOSS_DIE2)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		m_fDieEndTime +=  CTimeMgr::GetInstance()->GetPixelPerSec(); //�� ��ü �����ִ� �ð� ī��Ʈ
		if( m_fDieEndTime > 4.f )
		{
			DieCheck = true;
		}
	}
	else //���׾����� render
	{
		CDevice::GetInstance()->GetSprite()->End();
		CDevice::GetInstance()->GetDevice()->EndScene();

		CDevice::GetInstance()->GetDevice()->BeginScene();
		CDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BOSS, m_iStateID, int(m_fFrame))
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		CDevice::GetInstance()->GetSprite()->End();
		CDevice::GetInstance()->GetDevice()->EndScene();
		CDevice::GetInstance()->GetDevice()->BeginScene();
		CDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}
	//��Ʈ���̱�
	//CRectMgr::GetInstance()->Render(m_AtkRect,RECT_ID_ATK);
}
void CBoss1::DistanceChk(void)
{
	//�������� �Ÿ�, ������ �ٶ󺸴� ����
	//#study
	//���� �÷��̾���� �Ÿ��� �׻� ����ϰ�
	//�÷��̾ �ٶ󺸴� ������ ���Ͽ� �ٶ󺻴�

	m_vPlayerPos = m_pPlayer->GetInfo().vPos;
	D3DXVECTOR3 vDir =	m_vPlayerPos	- m_Info.vPos;

	m_fDistance	=	D3DXVec3Length(&vDir);

	D3DXVec3Normalize(&vDir,&vDir); //������ �Ÿ� ���� �����ְ� ��������ȭ

	m_Status.fAngle	=	acos(D3DXVec3Dot(&vDir,&m_Info.vLook));

	if( m_vPlayerPos.y > m_Info.vPos.y )
	{
		m_Status.fAngle = 2 * D3DX_PI - m_Status.fAngle; //���Ȱ�
	}

	m_Status.fAngle = D3DXToDegree(m_Status.fAngle);
	
}

void CBoss1::Pattern(void)
{
	//�Ÿ��� 75 ���ϸ� ������
	if(m_fDistance <= 75.f && m_iStateID != OBJECT_STATEID_BOSS_HIT1
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT2
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT3
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT4
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT5
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT6
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT7
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT8
		&& m_iStateID != OBJECT_STATEID_BOSS_DIE1
		&& m_iStateID != OBJECT_STATEID_BOSS_DIE2)
	{
		m_BestList.clear();
		Attack(m_Status.fAngle);
	}
	//�Ÿ��� 300 ���ϸ� �Ѿư���
	if(m_fDistance < 300.f && m_fDistance > 75.f &&  m_iStateID != OBJECT_STATEID_BOSS_DIE2)
	{
		if(m_fAstarTick > 2.f)
		{
			POINT MonsterPt,PlayerPt;
			PlayerPt.x = long(m_vPlayerPos.x);
			PlayerPt.y = long(m_vPlayerPos.y);

			MonsterPt.x = long(m_Info.vPos.x);
			MonsterPt.y = long(m_Info.vPos.y);

			for(size_t i=0; i < m_vecTile.size(); ++i)
			{
				if(CollisionMtoT(i,PlayerPt))
				{
					m_Status.Goal = i;
				}
				if(CollisionMtoT(i,MonsterPt))
				{
					m_Status.Now = i;
				}
			}	
			m_BestList = CAStar::GetInstance()->AStarStart(m_Status.Now,m_Status.Goal);
			
			Move(m_Status.fAngle);
			m_fAstarTick = 0.f;
		}
	}

	//�ǰ� 0�̵Ǹ� ���´�
	if(m_Status.iHp <= 0 && m_iStateID != OBJECT_STATEID_BOSS_DIE2)
	{
		DieTimeCount = true;

		if( m_iStateID = OBJECT_STATEID_BOSS_DIE1)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_DIE1;
		m_iMaxCnt = 25;
	}
}
void CBoss1::AStarMove( void )
{
	int		iIndex = m_BestList.front();
	
	D3DXVECTOR3 vDestPos = D3DXVECTOR3(m_vecTile[iIndex]->iX, m_vecTile[iIndex]->iY, 0.f);
	m_Info.vDir = vDestPos - m_Info.vPos;
	D3DXVec3Normalize(&m_Info.vDir,&m_Info.vDir);

	m_Info.vPos += m_Info.vDir * ACTMON1_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();

	if(m_fDistance < 20.0f)
	{
		m_BestList.pop_front();
	}
}

void CBoss1::Move( float m_fAngle )
{
	if(m_fAngle <= 292.5 && m_fAngle > 247.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN1)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN1;
		m_iMaxCnt = 5;
	}
	if(m_fAngle <= 247.5 && m_fAngle > 202.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN2)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN2;
		m_iMaxCnt = 5;
	}
	if(m_fAngle <= 202.5 && m_fAngle > 157.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN3)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN3;
		m_iMaxCnt = 5;
	}
	if(m_fAngle <= 157.5 && m_fAngle > 112.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN4)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN4;
		m_iMaxCnt = 5;
	}
	if(m_fAngle <= 112.5 && m_fAngle > 67.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN5)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN5;
		m_iMaxCnt = 5;
	}
	if(m_fAngle <= 67.5 && m_fAngle > 22.5)
	{
	;	if(m_iStateID == OBJECT_STATEID_BOSS_RUN6)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN6;
		m_iMaxCnt = 5;
	}
	if(m_fAngle > 337.5 || m_fAngle <= 22.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN7)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN7;
		m_iMaxCnt = 5;
	}
	if(m_fAngle <= 337.5 && m_fAngle > 292.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_RUN8)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_RUN8;
		m_iMaxCnt = 5;
	}

}

void CBoss1::Stand( float m_fAngle )
{

	if(m_fAngle <= 292.5 && m_fAngle > 247.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND1)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND1;
		m_iMaxCnt = 7;
	}
	if(m_fAngle <= 247.5 && m_fAngle > 202.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND2)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND2;
		m_iMaxCnt = 7;
	}
	if(m_fAngle <= 202.5 && m_fAngle > 157.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND3)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND3;
		m_iMaxCnt = 7;
	}
	if(m_fAngle <= 157.5 && m_fAngle > 112.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND4)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND4;
		m_iMaxCnt = 7;
	}
	if(m_fAngle <= 112.5 && m_fAngle > 67.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND5)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND5;
		m_iMaxCnt = 7;
	}
	if(m_fAngle <= 67.5 && m_fAngle > 22.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND6)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND6;
		m_iMaxCnt = 7;
	}
	if(m_fAngle > 337.5 || m_fAngle <= 22.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND7)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND7;
		m_iMaxCnt = 7;
	}
	if(m_fAngle <= 337.5 && m_fAngle > 292.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_STAND8)
			return;
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_STAND8;
		m_iMaxCnt = 7;
	}

}

void CBoss1::Attack( float m_fAngle )
{
	m_AtkRect.fSizeX = 30;
	m_AtkRect.fSizeY = 30;

	if(m_fAngle <= 292.5 && m_fAngle > 247.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK1)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x;
		m_AtkRect.fY = m_Info.vPos.y + 60;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK1;
		m_iMaxCnt = 18;
	}
	else if(m_fAngle <= 247.5 && m_fAngle > 202.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK2)
			return;

		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 30;
		m_AtkRect.fY = m_Info.vPos.y + 30;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK2;
		m_iMaxCnt = 18;
	}
	else if(m_fAngle <= 202.5 && m_fAngle > 157.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK3)
			return;

		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 60;
		m_AtkRect.fY = m_Info.vPos.y;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK3;
		m_iMaxCnt = 18;
	}
	else if(m_fAngle <= 157.5 && m_fAngle > 112.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK4)
			return;

		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x - 30;
		m_AtkRect.fY = m_Info.vPos.y - 30;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK4;
		m_iMaxCnt = 18;
	}
	else if(m_fAngle <= 112.5 && m_fAngle > 67.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK5)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x;
		m_AtkRect.fY = m_Info.vPos.y - 60;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK5;
		m_iMaxCnt = 18;
	}
	else if(m_fAngle <= 67.5 && m_fAngle > 22.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK6)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 30;
		m_AtkRect.fY = m_Info.vPos.y - 30;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK6;
		m_iMaxCnt = 18;
	}
	if(m_fAngle > 337.5 || m_fAngle <= 22.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK7)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 60;
		m_AtkRect.fY = m_Info.vPos.y;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK7;
		m_iMaxCnt = 18;
	}
	if(m_fAngle <= 337.5 && m_fAngle > 292.5)
	{
		if(m_iStateID == OBJECT_STATEID_BOSS_ATTACK8)
			return;
		m_fFrame = 0.f;
		m_AtkRect.fX = m_Info.vPos.x + 30;
		m_AtkRect.fY = m_Info.vPos.y + 30;
		m_iStateID = OBJECT_STATEID_BOSS_ATTACK8;
		m_iMaxCnt = 18;
	}
}

//�´¸��
void CBoss1::Hit(float m_fAngle) 
{
	if(m_fAngle <= 292.5 && m_fAngle > 247.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT1;
		m_iMaxCnt = 6;
	}
	else if(m_fAngle <= 247.5 && m_fAngle > 202.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT2;
		m_iMaxCnt = 6;
	}
	else if(m_fAngle <= 202.5 && m_fAngle > 157.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT3;
		m_iMaxCnt = 6;
	}
	else if(m_fAngle <= 157.5 && m_fAngle > 112.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT4;
		m_iMaxCnt = 6;
	}
	else if(m_fAngle <= 112.5 && m_fAngle > 67.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT5;
		m_iMaxCnt = 6;
	}
	else if(m_fAngle <= 67.5 && m_fAngle > 22.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT6;
		m_iMaxCnt = 6;
	}
	if(m_fAngle > 337.5 || m_fAngle <= 22.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT7;
		m_iMaxCnt = 6;
	}
	if(m_fAngle <= 337.5 && m_fAngle > 292.5)
	{
		m_fFrame = 0.f;
		m_iStateID = OBJECT_STATEID_BOSS_HIT8;
		m_iMaxCnt = 6;
	}
}
//��� �߰��Ҷ����� ���⿡�� �߰�
void CBoss1::RunToStand( void )
{
	if(m_BestList.empty() && m_iStateID != OBJECT_STATEID_BOSS_ATTACK1
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK2
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK3
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK4
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK5
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK6
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK7
		&& m_iStateID != OBJECT_STATEID_BOSS_ATTACK8
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT1
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT2
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT3
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT4
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT5
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT6
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT7
		&& m_iStateID != OBJECT_STATEID_BOSS_HIT8
		&& m_iStateID != OBJECT_STATEID_BOSS_DIE1
		&& m_iStateID != OBJECT_STATEID_BOSS_DIE2)
	{
		Stand(m_Status.fAngle);		
	}
}

bool CBoss1::CollisionMtoT(int iIndex, POINT ptMouse)
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

void CBoss1::Release( void )
{
}

CObj* CBoss1::Clone( void )
{
	return new CBoss1(*this);
}
