#include "StdAfx.h"
#include "Act2Proto.h"

#include "Player.h"
#include "Act2Back.h"

CAct2Proto::CAct2Proto(void)
{
	//�����ڿ� SetProto�� �־ m_mapObj�� Act�� �ʿ���
	//�����ؿ� �������� �־�д�
	SetProto();
}

CAct2Proto::~CAct2Proto(void)
{
}

void CAct2Proto::SetProto(void)
{
	INFO		Info;
	ZeroMemory(&Info, sizeof(Info));

	Info.vPos = D3DXVECTOR3(WINSIZEX / 2.f, WINSIZEY / 2.f, 0.f);
	Info.vLook = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&Info.matWorld);	 

	m_mapObj.insert(make_pair(OBJECT_BACKGROUND, new CAct2Back(Info)));	
	m_mapObj.insert(make_pair(OBJECT_PLAYER, new CPlayer(Info)));
}
