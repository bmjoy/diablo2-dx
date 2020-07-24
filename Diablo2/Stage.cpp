#include "StdAfx.h"
#include "Stage.h"

#include "TextureMgr.h"
#include "StageProto.h"
#include "ObjMgr.h"
#include "StateMgr.h"
#include "KeyMgr.h"
#include "WayPoint.h"
#include "QuestMgr.h"
#include "SoundMgr.h"

CStage::CStage(void)
{
}

CStage::CStage(int iData0, int iData1)
: CStateObj(iData0, iData1)
{

}

CStage::~CStage(void)
{
	Release();
}

void CStage::Initialize( void )
{
	CObjMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CQuestMgr::GetInstance()->DestroyInstance();
	CQuestMgr::GetInstance()->Initialize();
	CSoundMgr::GetInstance()->DestroyInstance();
	m_pObjProto = new CStageProto; //m_pObjProto�� ������ stage1�� �ִ� ��� object���� ������ �����Ҽ��� �ִ�


	
	//Ÿ��
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Tile/Tile0%d.png", TEXTYPE_MULTI, OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, TILENUM);
	//������Ʈ
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Object/%d.png", TEXTYPE_MULTI, OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_OBJECT, OBJNUM);

	//�������̽�
	//1.����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/stat.png", TEXTYPE_SINGLE, OBJECT_INFO, OBJECT_STATEID_INTERFACE_STATUS,1);
	//2.�г�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/hp.png", TEXTYPE_MULTI, OBJECT_PANEL, OBJECT_STATEID_PANEL_HP,1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/mana.png", TEXTYPE_MULTI, OBJECT_PANEL, OBJECT_STATEID_PANELE_MP,1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/panel.png", TEXTYPE_MULTI, OBJECT_PANEL, OBJECT_STATEID_PANEL_PANEL,1);
	//3.�κ��丮
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/inven.png", TEXTYPE_SINGLE, OBJECT_INVEN, OBJECT_STATEID_INVEN_INVEN,1);
	//4.����Ʈ
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/quest1.png", TEXTYPE_MULTI, OBJECT_QUEST, OBJECT_STATEID_QUEST_QUEST,1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/questalert.png", TEXTYPE_MULTI, OBJECT_QUEST, OBJECT_STATEID_QUEST_QUESTALERT,1);
	//5.��������Ʈ
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Waypoint/Waypoint%d.png", TEXTYPE_MULTI, OBJECT_WAYPOINT, OBJECT_STATEID_WAYPOINT_WAYPOINT, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Waypoint/waypoint.png", TEXTYPE_MULTI, OBJECT_WAYPOINT, OBJECT_STATEID_WAYPOINT_MENU, 1);
	//6.����Ʈ �Ŵ���
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/questalert.png", TEXTYPE_MULTI, OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALERT, 1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/questalram.png", TEXTYPE_MULTI, OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ALRAM, 1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/arrow.png", TEXTYPE_MULTI, OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_ARROW, 1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/player_talk.png", TEXTYPE_MULTI, OBJECT_QUESTMGR, OBJECT_STATEID_QUESTMGR_PLAYERTALK, 1);
	//NPC
	//1.������
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/Shop/Frame%d.png",TEXTYPE_MULTI, OBJECT_SHOPNPC, OBJECT_STATEID_SHOPNPC_SHOPNPC,13);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/shop.png",TEXTYPE_MULTI, OBJECT_SHOPNPC, OBJECT_STATEID_SHOPNPC_SHOPLIST,1);
	//2.���ǻ���
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/PotionShop/Frame%d.png",TEXTYPE_MULTI, OBJECT_PSHOPNPC, OBJECT_STATEID_PSHOPNPC_PSHOPNPC,12);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/shop.png",TEXTYPE_MULTI, OBJECT_PSHOPNPC, OBJECT_STATEID_PSHOPNPC_PSHOPLIST,1);
	//3.������(����Ʈ1)
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/isaac/issac%d.png", TEXTYPE_MULTI, OBJECT_ISAAC, OBJECT_STATEID_ISAAC_ISAAC,10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/isaac_talk.png", TEXTYPE_MULTI, OBJECT_ISAAC, OBJECT_STATEID_ISAAC_TALK, 1);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/God/Frame%d.png", TEXTYPE_MULTI, OBJECT_ISAAC, OBJECT_STATEID_ISAAC_GOD, 60); //����� ���� ����
		CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/god_talk.png", TEXTYPE_MULTI, OBJECT_ISAAC, OBJECT_STATEID_ISSAC_GTALK, 1);
	//4.���(����Ʈ2)
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/yuusha/yuusha%d.png", TEXTYPE_MULTI, OBJECT_YUUSHA, OBJECT_STATEID_YUUSHA_YUUSHA, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/yuusha_talk.png", TEXTYPE_MULTI, OBJECT_YUUSHA, OBJECT_STATEID_YUUSHA_TALK, 1);

	//5.�Ҵ�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/sonic/stand/Frame%d.png", TEXTYPE_MULTI, OBJECT_SONIC, OBJECT_STATEID_SONIC_NOMAL, 4);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Npc/sonic/help/Frame%d.png", TEXTYPE_MULTI, OBJECT_SONIC, OBJECT_STATEID_SONIC_HELP, 2);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Ui/sonic_talk.png", TEXTYPE_MULTI, OBJECT_SONIC, OBJECT_STATEID_SONIC_TALK, 1);

    //�÷��̾�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/1/01_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND1, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/2/02_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND2, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/3/03_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND3, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/4/04_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND4, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/5/05_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND5, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/6/06_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND6, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/7/07_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND7, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/8/08_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND8, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/9/09_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND9, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/10/10_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND10, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/11/11_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND11, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/12/12_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND12, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/13/13_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND13, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/14/14_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND14, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/15/15_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND15, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Stand/16/16_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_STAND16, 8);

	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/1/01_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN1, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/2/02_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN2, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/3/03_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN3, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/4/04_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN4, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/5/05_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN5, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/6/06_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN6, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/7/07_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN7, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/8/08_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN8, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/9/09_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN9, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/10/10_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN10, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/11/11_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN11, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/12/12_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN12, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/13/13_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN13, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/14/14_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN14, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/15/15_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN15, 8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Run/16/16_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_RUN16, 8);
								

	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/1/01_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK1, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/2/02_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK2, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/3/03_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK3, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/4/04_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK4, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/5/05_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK5, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/6/06_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK6, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/7/07_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK7, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/8/08_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK8, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/9/09_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK9, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/10/10_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK10, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/11/11_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK11, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/12/12_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK12, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/13/13_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK13, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/14/14_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK14, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/15/15_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK15, 18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Attack/16/16_f0%d.png", TEXTYPE_MULTI, OBJECT_PLAYER, OBJECT_STATEID_PLAYER_ATTACK16, 18);
	
	//����1

	//1.���ĵ�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/1/00_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND1, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/2/01_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND2, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/3/02_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND3, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/4/03_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND4, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/5/04_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND5, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/6/05_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND6, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/7/06_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND7, 10);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Stand/8/07_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_STAND8, 10);

	//2.�ɾ����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/1/00_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN1,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/2/01_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN2,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/3/02_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN3,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/4/03_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN4,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/5/04_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN5,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/6/05_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN6,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/7/06_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN7,8);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Run/8/07_f0%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1, OBJECT_STATEID_MONSTER_RUN8,8);

	//3.����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/1/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK1,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/2/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK2,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/3/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK3,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/4/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK4,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/5/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK5,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/6/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK6,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/7/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK7,19);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Atk/8/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_ATTACK8,19);

	//4.������
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/1/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT1,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/2/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT2,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/3/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT3,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/4/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT4,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/5/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT5,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/6/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT6,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/7/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT7,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Hit/8/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_HIT8,5);

	//5.�״���
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Die1/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_DIE1,14);
	
	//6.�ֱ�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/1/Die2/00.png",TEXTYPE_MULTI,OBJECT_MONSTER1,OBJECT_STATEID_MONSTER_DIE2,1);

	//����2

	//1.���ĵ� 
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND1, 6); // 12);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND2, 6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND3, 6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND4, 6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND5, 6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND6, 6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND7, 6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_STAND8, 6);

	//2.�ɾ����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/1/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN1,7); // 14);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/2/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN2,7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/3/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN3,7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/4/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN4,7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/5/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN5,7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/6/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN6,7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/7/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN7,7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Run/8/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2, OBJECT_STATEID_MONSTER2_RUN8,7);

	//3.����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/1/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK1,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/2/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK2,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/3/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK3,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/4/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK4,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/5/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK5,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/6/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK6,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/7/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK7,17);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Atk/8/Frame%d.png",TEXTYPE_MULTI, OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_ATTACK8,17);

	//4.������
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/1/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT1,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/2/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT2,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/3/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT3,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/4/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT4,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/5/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT5,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/6/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT6,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/7/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT7,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Hit/8/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_HIT8,5);

	//5.�״���
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Die1/Frame%d.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_DIE1,21);
	
	//6.�ֱ�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/2/Die2/00.png",TEXTYPE_MULTI,OBJECT_MONSTER2,OBJECT_STATEID_MONSTER2_DIE2,1);
	
	//����
	//1.���ĵ�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND1, 7); // 13);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND2, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND3, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND4, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND5, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND6, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND7, 7);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Stand/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_STAND8, 7);

	//2.�ɾ����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/1/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN1,5); // 13);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/2/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN2,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/3/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN3,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/4/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN4,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/5/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN5,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/6/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN6,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/7/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN7,5);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Run/8/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS, OBJECT_STATEID_BOSS_RUN8,5);

	//3.����
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/1/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK1,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/2/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK2,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/3/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK3,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/4/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK4,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/5/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK5,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/6/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK6,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/7/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK7,18);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Atk/8/Frame%d.png",TEXTYPE_MULTI, OBJECT_BOSS,OBJECT_STATEID_BOSS_ATTACK8,18);

	//4.������
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/1/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT1,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/2/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT2,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/3/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT3,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/4/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT4,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/5/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT5,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/6/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT6,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/7/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT7,6);
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Hit/8/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_HIT8,6);

	//5.�״���
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Die1/Frame%d.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_DIE1,25);
	
	//6.�ֱ�
	CTextureMgr::GetInstance()->AddTexture(L"../Texture/Monster/Act1/Boss/Die2/00.png",TEXTYPE_MULTI,OBJECT_BOSS,OBJECT_STATEID_BOSS_DIE2,1);
	///////////////////////////���� ��//////////////////////////

	//��׶���
	CObjMgr::GetInstance()->AddObject(OBJECT_BACKGROUND, m_pObjProto);
	//�÷��̾�
	CObjMgr::GetInstance()->AddObject(OBJECT_PLAYER, m_pObjProto);		
	//�������̽�
	CObjMgr::GetInstance()->AddObject(OBJECT_INFO, m_pObjProto);	
	CObjMgr::GetInstance()->AddObject(OBJECT_PANEL, m_pObjProto);	
	CObjMgr::GetInstance()->AddObject(OBJECT_INVEN, m_pObjProto);
	CObjMgr::GetInstance()->AddObject(OBJECT_QUEST, m_pObjProto);
	CObjMgr::GetInstance()->AddObject(OBJECT_WAYPOINT, m_pObjProto);
	//NPC��
	CObjMgr::GetInstance()->AddObject(OBJECT_SHOPNPC, m_pObjProto);	
	CObjMgr::GetInstance()->AddObject(OBJECT_PSHOPNPC, m_pObjProto);	
	CObjMgr::GetInstance()->AddObject(OBJECT_ISAAC, m_pObjProto);	
	CObjMgr::GetInstance()->AddObject(OBJECT_YUUSHA, m_pObjProto);	
	CObjMgr::GetInstance()->AddObject(OBJECT_SONIC, m_pObjProto);	

	//�� ��ġ
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER2, m_pObjProto,9000.f,400.f);	//����Ʈ1 ������ �ִ� ����, �� �ϼ���
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER2, m_pObjProto,8950.f,450.f);	//����Ʈ1 ������ �ִ� ����, �� �ϼ���
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER2, m_pObjProto,9000.f,500.f);	//����Ʈ1 ������ �ִ� ����, �� �ϼ���
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER2, m_pObjProto,9100.f,550.f);	//����Ʈ1 ������ �ִ� ����, �� �ϼ���
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER2, m_pObjProto,9000.f,550.f);	//����Ʈ1 ������ �ִ� ����, �� �ϼ���

	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER1, m_pObjProto,5500.f,1800.f);	//����Ʈ4 ������ �ִ� ��, �� �߾ӿ��� �Ʒ�
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER1, m_pObjProto,5530.f,1830.f);	//����Ʈ4 ������ �ִ� ��, �� �߾ӿ��� �Ʒ�
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER1, m_pObjProto,5470.f,1770.f);	//����Ʈ4 ������ �ִ� ��, �� �߾ӿ��� �Ʒ�
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER1, m_pObjProto,5560.f,1860.f);	//����Ʈ4 ������ �ִ� ��, �� �߾ӿ��� �Ʒ�
	CObjMgr::GetInstance()->AddObject(OBJECT_MONSTER1, m_pObjProto,5410.f,1850.f);	//����Ʈ4 ������ �ִ� ��, �� �߾ӿ��� �Ʒ�

	CObjMgr::GetInstance()->AddObject(OBJECT_BOSS, m_pObjProto,9000.f,1800.f); //act1 ����


	///////////////////////////����////////////////////////
	CSoundMgr::GetInstance()->Init();
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Act1/tristram.wav"); //�ʹ� ������� 0
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Act1/wild.wav"); //�Ҵ� ��ġ�� ����� 1
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/windowopen.wav"); //���� �������̽� ȿ���� 2
	//////�÷��̾�/////
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/cain.wav"); //������ �Ҵ� 3

	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Run/LightDirtRun1.wav"); //�޸��¼Ҹ� 4
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Run/LightDirtRun2.wav"); //�޸��¼Ҹ� 5
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Run/LightDirtRun3.wav"); //�޸��¼Ҹ� 6
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Run/LightDirtRun4.wav"); //�޸��¼Ҹ� 7

	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Playeratk/grunt101.wav"); //���ݽ� �÷��̾� ���� 8
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Playeratk/grunt102.wav"); //���ݽ� �÷��̾� ���� 9
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Playeratk/grunt103.wav"); //���ݽ� �÷��̾� ���� 10
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Playeratk/grunt201.wav"); //���ݽ� �÷��̾� ���� 11
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Playeratk/grunt202.wav"); //���ݽ� �÷��̾� ���� 12
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Playeratk/grunt203.wav"); //���ݽ� �÷��̾� ���� 13

	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladehit/blade1.wav"); //Ÿ�� ������ Ÿ�ݼҸ� 14
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladehit/blade2.wav"); //Ÿ�� ������ Ÿ�ݼҸ� 15
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladehit/blade3.wav"); //Ÿ�� ������ Ÿ�ݼҸ� 16 
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladehit/blade4.wav"); //Ÿ�� ������ Ÿ�ݼҸ� 17
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladehit/blade5.wav"); //Ÿ�� ������ Ÿ�ݼҸ� 18
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladehit/blade6.wav"); //Ÿ�� ������ Ÿ�ݼҸ� 19

	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladeatk/1.wav"); //Į �ֵθ��� �Ҹ� 20
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladeatk/2.wav"); //Į �ֵθ��� �Ҹ� 21
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladeatk/3.wav"); //Į �ֵθ��� �Ҹ� 22
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladeatk/4.wav"); //Į �ֵθ��� �Ҹ� 23
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladeatk/5.wav"); //Į �ֵθ��� �Ҹ� 24
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Player/Bladeatk/6.wav"); //Į �ֵθ��� �Ҹ� 25

	//////npc/////////
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Npc/Aka_orderwelcomes.wav"); //���Ǽ� �λ� 26
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Npc/Cha_heythere.wav"); //��� �λ� 27
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Npc/Ghe_hello.wav"); //��� �λ� 28

	/////����/////
	/////�޸�����/////
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/fallen/death1.wav"); //�޸������� 29
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/fallen/gethit1.wav"); //�޸������� 30

	///ī��////
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/gethit4.wav"); //ī�� ������ 31
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/gethit3.wav"); //ī�� ������ 32
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/gethit2.wav"); //ī�� ������ 33
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/gethit1.wav"); //ī�� ������ 34
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/neutral3.wav"); //ī�� �����ν��Ҷ� 35
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/death4.wav"); //ī�� ������		36
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/death5.wav"); //ī�� ������		37
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/moo/death3.wav"); //ī�� ������	38

	///���ǽ���
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/attack1.wav"); //���� �����Ҷ�	39
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/death.wav"); //���� ������	40
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/gethit1.wav"); //���� ������	41
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/gethit2.wav"); //���� ������	42
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/gethit3.wav"); //���� ������	43
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/gethit4.wav"); //���� ������	44
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Monster/mephisto/attack2.wav"); //���� �����Ҷ� 45
	CSoundMgr::GetInstance()->SoundPlay(0, 1);
}

void CStage::Progress( void )
{
	CQuestMgr::GetInstance()->Progress();

//Player�� �ִ� key���� �Լ����� �Ϸ��ϱ� �߾ȵǼ� �Ѱܻ���;;
	if( ((CWayPoint*)(CObjMgr::GetInstance()->GetObj(OBJECT_WAYPOINT,0)))->SwitchAct1() )
	{
		//�÷��̾� ������ ���� �����ϰ� �Ѱܾ��Ѵ�
		CStateMgr::GetInstance()->SetState(STATEID_ACT1);
		return;	
	}	
	if( ((CWayPoint*)(CObjMgr::GetInstance()->GetObj(OBJECT_WAYPOINT,0)))->SwitchAct2() )
	{
		CStateMgr::GetInstance()->SetState(STATEID_ACT2);
		return;	
	}	

	CObjMgr::GetInstance()->Progress();
}

void CStage::Render( void )
{
	CObjMgr::GetInstance()->Render();
}

void CStage::Release( void )
{
	SAFE_DELETE(m_pObjProto);
}

CStateObj* CStage::Clone( void )
{
	return new CStage(*this);
}
