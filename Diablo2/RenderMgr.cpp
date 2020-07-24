#include "StdAfx.h"
#include "RenderMgr.h"

CRenderMgr::CRenderMgr(void)
{
}

CRenderMgr::~CRenderMgr(void)
{
}

void CRenderMgr::Render(void)
{

}

void CRenderMgr::ArrayYpos(map<int,list<CObj*>>* _YSortMap)
{
	map<int,list<CObj*>>::iterator mon1 = _YSortMap->find(OBJECT_MONSTER1);
	map<int,list<CObj*>>::iterator mon2 = _YSortMap->find(OBJECT_MONSTER2);
	map<int,list<CObj*>>::iterator boss = _YSortMap->find(OBJECT_BOSS);
	map<int,list<CObj*>>::iterator player = _YSortMap->find(OBJECT_PLAYER);

	map<int,list<CObj*>>::iterator Isaac = _YSortMap->find(OBJECT_ISAAC);
	map<int,list<CObj*>>::iterator yuusha = _YSortMap->find(OBJECT_YUUSHA);
	map<int,list<CObj*>>::iterator sonic = _YSortMap->find(OBJECT_SONIC);
	map<int,list<CObj*>>::iterator shopnpc = _YSortMap->find(OBJECT_SHOPNPC);
	map<int,list<CObj*>>::iterator pshopnpc = _YSortMap->find(OBJECT_PSHOPNPC);



}

//void CRenderMgr::ArrayYpos(OBJLIST *_ObjList)
//{
//	for( size_t i = OBJ_STAGE_MONSTER1; i < OBJ_STAGE_INTERFACE; ++i)
//	{
//		for(OBJITER iter = _ObjList[i].begin(); iter != _ObjList[i].end(); ++iter)
//		{
//			m_RenderMgr.insert( pair<float,CObj*>((*iter)->GetInfo().fY , (*iter)));
//		}
//	}
//}

	//multimap<float,CObj*>	m_YposRender;