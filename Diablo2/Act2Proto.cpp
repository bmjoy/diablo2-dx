#include "StdAfx.h"
#include "Act2Proto.h"

#include "Player.h"
#include "Act2Back.h"

CAct2Proto::CAct2Proto(void)
{
	//생성자에 SetProto가 있어서 m_mapObj에 Act에 필요한
	//복사해올 원형들을 넣어둔다
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
