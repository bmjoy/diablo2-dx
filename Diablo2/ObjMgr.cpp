#include "StdAfx.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Boss1.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "RandomMgr.h"
#include "RenderMgr.h"

//������Ʈ��(player,npc,monster)�� ��ȣ�ۿ�(Ÿ��,��ȭ) ó��
CObjMgr::CObjMgr(void)
: m_fTick(0.f)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}


void CObjMgr::Progress(void)
{
	ClickMonster();
	
	CRenderMgr::GetInstance()->ArrayYpos(&m_MapObj);

	for (map<int, list<CObj*>>::iterator	iter = m_MapObj.begin();
		iter != m_MapObj.end(); ++iter)
	{
		for (list<CObj*>::iterator	iter1 = iter->second.begin();
			iter1 != iter->second.end(); ++iter1)
		{
			(*iter1)->Progress();
		}
	}

}
void CObjMgr::Render(void)
{
//	map<int,list<CObj*>>::iterator BackGround = m_MapObj.find(OBJECT_BACKGROUND);
//	map<int,list<CObj*>>::iterator WayPoint = m_MapObj.find(OBJECT_WAYPOINT);
//
//
//	map<int,list<CObj*>>::iterator Panel = m_MapObj.find(OBJECT_PANEL);
//	map<int,list<CObj*>>::iterator Info = m_MapObj.find(OBJECT_INFO);
//	map<int,list<CObj*>>::iterator Inven = m_MapObj.find(OBJECT_INVEN);
//	map<int,list<CObj*>>::iterator Quest = m_MapObj.find(OBJECT_QUEST);
//	map<int,list<CObj*>>::iterator QuestMgr = m_MapObj.find(OBJECT_QUESTMGR);
//
//////////////////////////////////////////////////////////////////
//	for (list<CObj*>::iterator	iter = BackGround->second.begin();
//		iter != BackGround->second.end(); ++iter)
//	{
//		(*iter)->Render();
//	}
//
//	if( WayPoint == m_MapObj.end() && Panel == m_MapObj.end()
//		&& Info == m_MapObj.end() && Inven == m_MapObj.end() && Quest == m_MapObj.end()
//		&& QuestMgr == m_MapObj.end())
//		return;
//
//	if(WayPoint != m_MapObj.end())
//	{
//		for (list<CObj*>::iterator	iter = WayPoint->second.begin();
//			iter != WayPoint->second.end(); ++iter)
//		{
//			(*iter)->Render();
//		}
//	}
//
///////////////////////////////////////////////////////////////
//
//	
//
///////////////////////////////////////////////////////////////
//
//	if(Panel != m_MapObj.end())
//	{
//		for (list<CObj*>::iterator	iter = Panel->second.begin();
//			iter != Panel->second.end(); ++iter)
//		{
//			(*iter)->Render();
//		}
//	}
//
//	if(Info != m_MapObj.end())
//	{
//		for (list<CObj*>::iterator	iter = Info->second.begin();
//			iter != Info->second.end(); ++iter)
//		{
//			(*iter)->Render();
//		}
//	}
//	if(Inven != m_MapObj.end())
//	{
//		for (list<CObj*>::iterator	iter = Inven->second.begin();
//			iter != Inven->second.end(); ++iter)
//		{
//			(*iter)->Render();
//		}
//	}
//	if(Quest != m_MapObj.end())
//	{
//		for (list<CObj*>::iterator	iter = Quest->second.begin();
//			iter != Quest->second.end(); ++iter)
//		{
//			(*iter)->Render();
//		}
//	}
//	if(QuestMgr != m_MapObj.end())
//	{
//		for (list<CObj*>::iterator	iter = QuestMgr->second.begin();
//			iter != QuestMgr->second.end(); ++iter)
//		{
//			(*iter)->Render();
//		}
//	}
	for (map<int, list<CObj*>>::iterator	iter = m_MapObj.begin();
		iter != m_MapObj.end(); ++iter)
	{
		for (list<CObj*>::iterator	iter1 = iter->second.begin();
			iter1 != iter->second.end(); ++iter1)
		{
			(*iter1)->Render();
		}
	}
}

//act���� �����ؼ� ����ҵ�
void CObjMgr::ClickMonster(void)
{
//#Study
//�� ���͵��� ��Ʈ�ȿ� �� ���콺 Ŀ�Ű� ���ִ��� üũ�Ѵ�
//ACT�� �� ������ 3���� �׸��� mapobj�ȿ� 3������ ������ ������ 3�� �� �˻��Ѵ�
	map<int,list<CObj*>>::iterator Player = m_MapObj.find(OBJECT_PLAYER);
	map<int,list<CObj*>>::iterator Mon1 = m_MapObj.find(OBJECT_MONSTER1);
	map<int,list<CObj*>>::iterator Mon2 = m_MapObj.find(OBJECT_MONSTER2);
	map<int,list<CObj*>>::iterator Boss	 = m_MapObj.find(OBJECT_BOSS);

	//m_fTick	+=	 CTimeMgr::GetInstance()->GetPixelPerSec();
	RECT rc;

	if( Mon1 == m_MapObj.end() && Mon2 == m_MapObj.end() && Boss == m_MapObj.end())
		return;

	//����1
	if(Mon1 != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Mon1->second.begin(); iter != Mon1->second.end(); ++iter)
		{
			POINT MousePt = CMouseMgr::GetMousePos(); 
			D3DXVECTOR3 vDir = (*iter)->GetInfo().vPos - Player->second.front()->GetInfo().vPos;
		
			if( IntersectRect(&rc,&(Player->second.front())->GetAtkRect(),&(*iter)->GetObjRect()))
			{	
				if( (*iter)->GetDealTime() > 1.f) //DPS
				{				
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(14,19),0); //�´¼Ҹ�
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(31,34),0); //���´¼Ҹ�
					(*iter)->ResetDealTime();
					((CMonster1*)(*iter))->Hit((*iter)->GetStat().fAngle);
					((CMonster1*)(*iter))->SetHp(Player->second.front()->GetStat().iAtk);
				}
			}

			if(PtInRect(&((*iter)->GetObjRect()),MousePt))
			{		
				if( PUSH_KEY(KEY_LBUTTON))
				{
					//ERRORCHK(L"�� Ŭ�� üũ");
					//�Ÿ��� 75 �����϶��� ��Ÿ�� �����Ѵ�
					if( D3DXVec3Length(&vDir) <= 75 )
					{
						SetDirMotion((*iter)->GetInfo().vPos.x ,(*iter)->GetInfo().vPos.y); //���� �ٶ󺸴� ���� ���ϱ�
						((CPlayer*)Player->second.front())->ClearBestList();
						((CPlayer*)Player->second.front())->PlayerAtk(((CPlayer*)Player->second.front())->GetStat().fAngle);
					}
				}
			}

		}
	}
	//���� ������ ������
	if(Mon1 != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Mon1->second.begin(); iter != Mon1->second.end();)
		{

			if( (*iter)->GetStat().iHp <= 0 && ((CMonster1*)(*iter))->GetDieCheck() )
			{
				CQuestMgr::GetInstance()->SetKillCount2(); //����Ʈ2 �� ų�� ī��Ʈ
				SAFE_DELETE(*iter);
				iter = Mon1->second.erase(iter);
			}
			else
				 ++iter;
		}
	}

	//����2 
	if(Mon2 != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Mon2->second.begin(); iter != Mon2->second.end(); ++iter)
		{
			POINT MousePt = CMouseMgr::GetMousePos(); 
			D3DXVECTOR3 vDir = (*iter)->GetInfo().vPos - Player->second.front()->GetInfo().vPos;
		
			if( IntersectRect(&rc,&(Player->second.front())->GetAtkRect(),&(*iter)->GetObjRect()))
			{	
				if( (*iter)->GetDealTime() > 1.f) //DPS
				{					
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(14,19),0); //�´¼Ҹ�
					CSoundMgr::GetInstance()->SoundPlay(30,0); //���´¼Ҹ�
					(*iter)->ResetDealTime();
					((CMonster2*)(*iter))->Hit((*iter)->GetStat().fAngle);
					((CMonster2*)(*iter))->SetHp(Player->second.front()->GetStat().iAtk);
				}
			}

			if(PtInRect(&((*iter)->GetObjRect()),MousePt))
			{		
				if( PUSH_KEY(KEY_LBUTTON))
				{
					//ERRORCHK(L"�� Ŭ�� üũ");
					//�Ÿ��� 75 �����϶��� ��Ÿ�� �����Ѵ�
					if( D3DXVec3Length(&vDir) <= 75 )
					{
						SetDirMotion((*iter)->GetInfo().vPos.x ,(*iter)->GetInfo().vPos.y); //���� �ٶ󺸴� ���� ���ϱ�
						((CPlayer*)Player->second.front())->ClearBestList();
						((CPlayer*)Player->second.front())->PlayerAtk(((CPlayer*)Player->second.front())->GetStat().fAngle);
					}
				}
			}

		}
	}
	//���� ������ ������
	if(Mon2 != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Mon2->second.begin(); iter != Mon2->second.end();)
		{

			if( (*iter)->GetStat().iHp <= 0 && ((CMonster2*)(*iter))->GetDieCheck() )
			{
				CQuestMgr::GetInstance()->SetKillCount1(); //����Ʈ1 �� ų�� ī��Ʈ
				SAFE_DELETE(*iter);
				iter = Mon2->second.erase(iter);
			}
			else
				 ++iter;
		}
	}

	//����
	if(Boss != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Boss->second.begin(); iter != Boss->second.end(); ++iter)
		{
			POINT MousePt = CMouseMgr::GetMousePos(); 
			D3DXVECTOR3 vDir = (*iter)->GetInfo().vPos - Player->second.front()->GetInfo().vPos;
		
			if( IntersectRect(&rc,&(Player->second.front())->GetAtkRect(),&(*iter)->GetObjRect()))
			{	
				if( (*iter)->GetDealTime() > 1.f) //DPS
				{					
					(*iter)->ResetDealTime();
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(14,19),0); //�´¼Ҹ�
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(41,44),0); //���´¼Ҹ�
					((CBoss1*)(*iter))->Hit((*iter)->GetStat().fAngle);
					((CBoss1*)(*iter))->SetHp(Player->second.front()->GetStat().iAtk);
				}
			}

			if(PtInRect(&((*iter)->GetObjRect()),MousePt))
			{		
				if( PUSH_KEY(KEY_LBUTTON))
				{
					//ERRORCHK(L"�� Ŭ�� üũ");
					//�Ÿ��� 75 �����϶��� ��Ÿ�� �����Ѵ�
					if( D3DXVec3Length(&vDir) <= 75 )
					{
						SetDirMotion((*iter)->GetInfo().vPos.x ,(*iter)->GetInfo().vPos.y); //���� �ٶ󺸴� ���� ���ϱ�
						((CPlayer*)Player->second.front())->ClearBestList();
						((CPlayer*)Player->second.front())->PlayerAtk(((CPlayer*)Player->second.front())->GetStat().fAngle);
					}
				}
			}

		}
	}
	//���� ������ ������
	if(Boss != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Boss->second.begin(); iter != Boss->second.end();)
		{

			if( (*iter)->GetStat().iHp <= 0 && ((CBoss1*)(*iter))->GetDieCheck() )
			{
				CQuestMgr::GetInstance()->SetKillCount3(); //����Ʈ3 �� ų�� ī��Ʈ
				SAFE_DELETE(*iter);
				iter = Boss->second.erase(iter);
			}
			else
				 ++iter;
		}
	}
}

void CObjMgr::SetDirMotion(float fX, float fY)
{
	map<int,list<CObj*>>::iterator iter = m_MapObj.find(OBJECT_PLAYER);

	D3DXVECTOR3 vDestPos = D3DXVECTOR3( fX , fY , 0.f);
	D3DXVECTOR3 vDir = vDestPos - iter->second.front()->GetInfo().vPos;
	D3DXVECTOR3 vLook = iter->second.front()->GetInfo().vLook;


	float fDistance = D3DXVec3Length(&vDir);
	
	D3DXVec3Normalize(&vDir,&vDir);
	
	float fAngle = acosf(D3DXVec3Dot(&vDir, &vLook));

	if( fY > iter->second.front()->GetInfo().vPos.y )
	{
		fAngle = 2 * D3DX_PI - fAngle; //���Ȱ�
	}
		
	fAngle = D3DXToDegree(fAngle);
	((CPlayer*)iter->second.front())->SetAngle(fAngle);
}

CObj*	CObjMgr::GetObj(int iObjID, int Cnt)
{
	//#Study
	//���ϴ� ������Ʈ�� �� list�� ã�Ƴ���
	map<int,list<CObj*>>::iterator iter = m_MapObj.find(iObjID);
	if( iter == m_MapObj.end())
	{
		return NULL;
	}

	
	list<CObj*>::iterator iter1 = iter->second.begin();
	if( iter1 == iter->second.end())
	{
		return NULL;
	}
 //list�ȿ��� ���� ���ϴ� ��ġ�� �������� cnt��ŭ iter�� ������
	for( int i = 0; i < Cnt;++i)
	{
		++iter1;

		if( iter1 == iter->second.end() )
			return NULL;
	}
	return (*iter1);
}

void CObjMgr::Release(void)
{
	for (map<int, list<CObj*>>::iterator	iter = m_MapObj.begin();
		iter != m_MapObj.end(); ++iter)
	{
		for (list<CObj*>::iterator	iter1 = iter->second.begin();
			iter1 != iter->second.end(); ++iter1)
		{
			SAFE_DELETE(*iter1);
		}
		iter->second.clear();
	}
	m_MapObj.clear();
}