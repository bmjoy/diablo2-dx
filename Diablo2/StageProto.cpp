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

	//����â
	m_mapObj.insert(make_pair(OBJECT_INFO, new CInfo()));

	//�����г�â
	m_mapObj.insert(make_pair(OBJECT_PANEL, new CPanel()));

	//�κ�
	m_mapObj.insert(make_pair(OBJECT_INVEN, new CInven()));

	//����Ʈ
	m_mapObj.insert(make_pair(OBJECT_QUEST, new CQuest()));

	//��������Ʈ
	m_mapObj.insert(make_pair(OBJECT_WAYPOINT, new CWayPoint()));

	//������NPC
	m_mapObj.insert(make_pair(OBJECT_SHOPNPC, new CShopNpc()));

	//���ǻ���NPC
	m_mapObj.insert(make_pair(OBJECT_PSHOPNPC, new CPshopNpc()));

	//������(����Ʈ1)
	m_mapObj.insert(make_pair(OBJECT_ISAAC, new CIsaac()));

	//���(����Ʈ2)
	m_mapObj.insert(make_pair(OBJECT_YUUSHA, new CYuusha()));

	//�Ҵ�
	m_mapObj.insert(make_pair(OBJECT_SONIC, new CSonic()));
}

