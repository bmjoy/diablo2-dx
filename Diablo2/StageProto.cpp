#include "StdAfx.h"
#include "StageProto.h"

#include "BackGround.h"
#include "Player.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Boss1.h"
#include "Info.h"
#include "Panel.h"
#include "Inven.h"
#include "Quest.h"
#include "ShopNpc.h"
#include "PshopNpc.h"
#include "Isaac.h"
#include "Yuusha.h"
#include "WayPoint.h"
#include "Sonic.h"


CStageProto::CStageProto(void)
{
	SetProto();
}

CStageProto::~CStageProto(void)
{

}


void CStageProto::SetProto(void)
{
	INFO				Info;
	ZeroMemory(&Info, sizeof(Info));

	Info.vPos = D3DXVECTOR3(WINSIZEX / 2.f, WINSIZEY / 2.f, 0.f);
	Info.vLook = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&Info.matWorld);	

	m_mapObj.insert(make_pair(OBJECT_BACKGROUND, new CBackGround(Info)));	
	m_mapObj.insert(make_pair(OBJECT_PLAYER, new CPlayer(Info)));
	m_mapObj.insert(make_pair(OBJECT_MONSTER1, new CMonster1(Info)));
	m_mapObj.insert(make_pair(OBJECT_MONSTER2, new CMonster2()));
	m_mapObj.insert(make_pair(OBJECT_BOSS, new CBoss1()));

	//스텟창
	m_mapObj.insert(make_pair(OBJECT_INFO, new CInfo()));

	//메인패널창
	m_mapObj.insert(make_pair(OBJECT_PANEL, new CPanel()));

	//인벤
	m_mapObj.insert(make_pair(OBJECT_INVEN, new CInven()));

	//퀘스트
	m_mapObj.insert(make_pair(OBJECT_QUEST, new CQuest()));

	//웨이포인트
	m_mapObj.insert(make_pair(OBJECT_WAYPOINT, new CWayPoint()));

	//장비상점NPC
	m_mapObj.insert(make_pair(OBJECT_SHOPNPC, new CShopNpc()));

	//포션상점NPC
	m_mapObj.insert(make_pair(OBJECT_PSHOPNPC, new CPshopNpc()));

	//아이작(퀘스트1)
	m_mapObj.insert(make_pair(OBJECT_ISAAC, new CIsaac()));

	//용사(퀘스트2)
	m_mapObj.insert(make_pair(OBJECT_YUUSHA, new CYuusha()));

	//소닉
	m_mapObj.insert(make_pair(OBJECT_SONIC, new CSonic()));
}

