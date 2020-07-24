#include "StdAfx.h"
#include "Act2Back.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"
#include "AStar.h"
#include "ObjMgr.h"

#include "KeyMgr.h"

CAct2Back::CAct2Back(void)
{
}

CAct2Back::CAct2Back(const INFO& Info)
: CObj(Info)
{

}

CAct2Back::~CAct2Back(void)
{
	Release();
}

void CAct2Back::Initialize(void)
{
	InitTile();

}

void CAct2Back::Progress(void)
{
}

void CAct2Back::Render(void)
{
	D3DXMATRIX			matTrans;
	
	PlayerOnTile();

	for( int i = 0; i < 19; ++i )
	{
		for( int j = 0; j < 7; ++j)
		{
			//���� ���ִ� index - 543��° Ÿ�Ϻ��� ���η� 19ĭ ���η� 7ĭ �Ѹ��鼭 ���ٴ¶�
			//Ÿ���� ������ �ٲ�� 543�� �ٲ���� �Ѵ�
			//��ü������ ���� ���� 2ĭ�� ������ �༭ Ÿ�� �򸮴� ����� �ȳ����� ��
			int iIndex =    i * ACT2_TILEX + (j+(m_iPlayerIdx-543));

			if(iIndex < 0
				|| iIndex >= ACT2_TILEX * ACT2_TILEY)
				continue;

			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
				, m_vecTile[iIndex]->iY, 0.f);

			m_Info.matWorld = matTrans;

			m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
				, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}

	for( list<POBJECT>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
		float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();

		(*iter)->iX -= fX;
		(*iter)->iY -= fY;

		D3DXMatrixTranslation(&matTrans, (*iter)->iX  - 200
			, (*iter)->iY - 300, 0.f);

		m_Info.matWorld = matTrans;

		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_OBJECT, (*iter)->iDrawID)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CAct2Back::InitTile(void)
{
	HANDLE			hFile;
	DWORD			dwByte;

	hFile = CreateFile(L"../Data/Act2/act2.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL, NULL);

	int		iCnt = 0;

	ReadFile(hFile, &iCnt, sizeof(int), &dwByte, NULL);

	for (int i = 0; i < iCnt; ++i)
	{
		PTILE	pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);
		m_vecTile.push_back(pTile);
	}

	int		iCnt1 = 0;

	ReadFile(hFile, &iCnt1, sizeof(int), &dwByte, NULL);

	for (int i = 0; i < iCnt1; ++i)
	{
		POBJECT		pObj = new OBJECT;
		ReadFile(hFile, pObj, sizeof(OBJECT), &dwByte, NULL);
		m_listObject.push_back(pObj);
	}
	CloseHandle(hFile);
}

void CAct2Back::Release( void )
{
	for(size_t i =0; i < m_vecTile.size(); ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}
	m_vecTile.clear();

	for(list<POBJECT>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

CObj* CAct2Back::Clone( void )
{
	return new CAct2Back(*this);
}

void CAct2Back::PlayerOnTile( void )
{
	//��Ÿ�� �̵�(�ø���)
	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();

	PlayerPos.x = long(CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vPos.x);
	PlayerPos.y = long(CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vPos.y);

 //���� ���ִ� Ÿ���� �ε����� �޾ƿ�
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(CollsionPtoT( i , PlayerPos))
		{
			m_iPlayerIdx = i; 
		}
		m_vecTile[i]->iX -= fX;
		m_vecTile[i]->iY -= fY;	
	}
}

bool CAct2Back::CollsionPtoT( int iIndex, POINT PlayerPos )
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

	if(PlayerPos.y - fGrad * PlayerPos.x - b[0] <= 0
		&& PlayerPos.y - -fGrad * PlayerPos.x - b[1] <= 0
		&& PlayerPos.y - fGrad * PlayerPos.x - b[2] > 0
		&& PlayerPos.y - -fGrad * PlayerPos.x - b[3] > 0)
	{
		return true;
	}
	return false;
}

