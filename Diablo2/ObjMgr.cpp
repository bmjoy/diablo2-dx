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

//오브젝트간(player,npc,monster)간 상호작용(타격,대화) 처리
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

//act별로 구분해서 써야할듯
void CObjMgr::ClickMonster(void)
{
//#Study
//각 몬스터들의 렉트안에 내 마우스 커셔가 들어가있는지 체크한다
//ACT당 몹 종류가 3개씩 그리고 mapobj안에 3종류로 나뉘어 있으니 3개 다 검사한다
	map<int,list<CObj*>>::iterator Player = m_MapObj.find(OBJECT_PLAYER);
	map<int,list<CObj*>>::iterator Mon1 = m_MapObj.find(OBJECT_MONSTER1);
	map<int,list<CObj*>>::iterator Mon2 = m_MapObj.find(OBJECT_MONSTER2);
	map<int,list<CObj*>>::iterator Boss	 = m_MapObj.find(OBJECT_BOSS);

	//m_fTick	+=	 CTimeMgr::GetInstance()->GetPixelPerSec();
	RECT rc;

	if( Mon1 == m_MapObj.end() && Mon2 == m_MapObj.end() && Boss == m_MapObj.end())
		return;

	//몬스터1
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
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(14,19),0); //맞는소리
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(31,34),0); //몹맞는소리
					(*iter)->ResetDealTime();
					((CMonster1*)(*iter))->Hit((*iter)->GetStat().fAngle);
					((CMonster1*)(*iter))->SetHp(Player->second.front()->GetStat().iAtk);
				}
			}

			if(PtInRect(&((*iter)->GetObjRect()),MousePt))
			{		
				if( PUSH_KEY(KEY_LBUTTON))
				{
					//ERRORCHK(L"몹 클릭 체크");
					//거리가 75 이하일때만 평타로 공격한다
					if( D3DXVec3Length(&vDir) <= 75 )
					{
						SetDirMotion((*iter)->GetInfo().vPos.x ,(*iter)->GetInfo().vPos.y); //몹을 바라보는 각도 구하기
						((CPlayer*)Player->second.front())->ClearBestList();
						((CPlayer*)Player->second.front())->PlayerAtk(((CPlayer*)Player->second.front())->GetStat().fAngle);
					}
				}
			}

		}
	}
	//몹이 죽으면 지우자
	if(Mon1 != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Mon1->second.begin(); iter != Mon1->second.end();)
		{

			if( (*iter)->GetStat().iHp <= 0 && ((CMonster1*)(*iter))->GetDieCheck() )
			{
				CQuestMgr::GetInstance()->SetKillCount2(); //퀘스트2 몹 킬링 카운트
				SAFE_DELETE(*iter);
				iter = Mon1->second.erase(iter);
			}
			else
				 ++iter;
		}
	}

	//몬스터2 
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
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(14,19),0); //맞는소리
					CSoundMgr::GetInstance()->SoundPlay(30,0); //몹맞는소리
					(*iter)->ResetDealTime();
					((CMonster2*)(*iter))->Hit((*iter)->GetStat().fAngle);
					((CMonster2*)(*iter))->SetHp(Player->second.front()->GetStat().iAtk);
				}
			}

			if(PtInRect(&((*iter)->GetObjRect()),MousePt))
			{		
				if( PUSH_KEY(KEY_LBUTTON))
				{
					//ERRORCHK(L"몹 클릭 체크");
					//거리가 75 이하일때만 평타로 공격한다
					if( D3DXVec3Length(&vDir) <= 75 )
					{
						SetDirMotion((*iter)->GetInfo().vPos.x ,(*iter)->GetInfo().vPos.y); //몹을 바라보는 각도 구하기
						((CPlayer*)Player->second.front())->ClearBestList();
						((CPlayer*)Player->second.front())->PlayerAtk(((CPlayer*)Player->second.front())->GetStat().fAngle);
					}
				}
			}

		}
	}
	//몹이 죽으면 지우자
	if(Mon2 != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Mon2->second.begin(); iter != Mon2->second.end();)
		{

			if( (*iter)->GetStat().iHp <= 0 && ((CMonster2*)(*iter))->GetDieCheck() )
			{
				CQuestMgr::GetInstance()->SetKillCount1(); //퀘스트1 몹 킬링 카운트
				SAFE_DELETE(*iter);
				iter = Mon2->second.erase(iter);
			}
			else
				 ++iter;
		}
	}

	//보스
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
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(14,19),0); //맞는소리
					CSoundMgr::GetInstance()->SoundPlay(CRandomMgr::GetInstance()->Random(41,44),0); //몹맞는소리
					((CBoss1*)(*iter))->Hit((*iter)->GetStat().fAngle);
					((CBoss1*)(*iter))->SetHp(Player->second.front()->GetStat().iAtk);
				}
			}

			if(PtInRect(&((*iter)->GetObjRect()),MousePt))
			{		
				if( PUSH_KEY(KEY_LBUTTON))
				{
					//ERRORCHK(L"몹 클릭 체크");
					//거리가 75 이하일때만 평타로 공격한다
					if( D3DXVec3Length(&vDir) <= 75 )
					{
						SetDirMotion((*iter)->GetInfo().vPos.x ,(*iter)->GetInfo().vPos.y); //몹을 바라보는 각도 구하기
						((CPlayer*)Player->second.front())->ClearBestList();
						((CPlayer*)Player->second.front())->PlayerAtk(((CPlayer*)Player->second.front())->GetStat().fAngle);
					}
				}
			}

		}
	}
	//몹이 죽으면 지우자
	if(Boss != m_MapObj.end())
	{
		for( list<CObj*>::iterator iter = Boss->second.begin(); iter != Boss->second.end();)
		{

			if( (*iter)->GetStat().iHp <= 0 && ((CBoss1*)(*iter))->GetDieCheck() )
			{
				CQuestMgr::GetInstance()->SetKillCount3(); //퀘스트3 몹 킬링 카운트
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
		fAngle = 2 * D3DX_PI - fAngle; //라디안값
	}
		
	fAngle = D3DXToDegree(fAngle);
	((CPlayer*)iter->second.front())->SetAngle(fAngle);
}

CObj*	CObjMgr::GetObj(int iObjID, int Cnt)
{
	//#Study
	//원하는 오브젝트가 들어간 list를 찾아낸다
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
 //list안에서 내가 원하는 위치로 가기위해 cnt만큼 iter를 돌린다
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