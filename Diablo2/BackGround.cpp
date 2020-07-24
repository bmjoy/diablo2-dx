#include "StdAfx.h"
#include "BackGround.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"
#include "AStar.h"
#include "ObjMgr.h"

#include "KeyMgr.h"
#include "Player.h"
#include "ScrollMgr.h"
#include	"TextMgr.h"

//캐릭터는 백그라운드가 움직이는 형태로 움직인다

CBackGround::CBackGround(void)
{
}

CBackGround::CBackGround(const INFO& Info)
: CObj(Info)
{

}

CBackGround::~CBackGround(void)
{
	Release();
}

void CBackGround::Initialize( void )
{
	InitTile();
}

void CBackGround::Progress( void )
{

}

void CBackGround::Render( void )
{
	D3DXMATRIX			matTrans;

//	TCHAR				szIdx[128];
	
	//for (size_t i = 0; i < m_vecTile.size(); ++i)
	//{
	//	
	//	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* 300.0f * CTimeMgr::GetInstance()->GetPixelPerSec();
	//	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* 300.0f * CTimeMgr::GetInstance()->GetPixelPerSec();

	//	m_vecTile[i]->iX -= fX;
	//	m_vecTile[i]->iY -= fY;

	//	D3DXMatrixTranslation(&matTrans, m_vecTile[i]->iX
	//		, m_vecTile[i]->iY, 0.f);

	//	m_Info.matWorld = matTrans;

	//	m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);

	//	CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
	//	CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[i]->iDrawID)
	//		, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//	//wsprintf(szIdx, L"%d", i);

	//	//RECT		rcFont = {0};

	//	//CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), szIdx, lstrlen(szIdx), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}

	float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
	
	PlayerPos.x = long(CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vPos.x);
	PlayerPos.y = long(CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vPos.y);

////내가 서있는 타일 인덱스 구하기,	맵타일 이동(컬링용)
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(CollsionPtoT( i , PlayerPos))
		{
			m_iPlayerIdx = i;  //내가 서있는 타일의 인덱스를 받아옴
		}

		m_vecTile[i]->iX -= fX;
		m_vecTile[i]->iY -= fY;		
	}
/////////////////////////////////////////////////////////////////////////////////////

	for( int i = 0; i < 19; ++i )
	{
		for( int j = 0; j < 7; ++j)
		{
			//내가 서있는 index - 543번째 타일부터 세로로 19칸 가로로 7칸 뿌리면서 간다는뜻
			//타일의 구성이 바뀌면 543을 바꿔줘야 한다
			//전체적으로 가로 세로 2칸씩 여유를 줘서 타일 깔리는 모습이 안나오게 함
			int iIndex = i * ACT1_TILEX + (j+(m_iPlayerIdx-543)); 
			
			if(iIndex < 0
				|| iIndex >= ACT1_TILEX * ACT1_TILEY)
				continue;
		
		D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->iX
			, m_vecTile[iIndex]->iY, 0.f);

		m_Info.matWorld = matTrans;

		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

////타일넘버 보기
//		wsprintf(szIdx, L"%d", iIndex);
//		RECT		rcFont = {0};
//		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), szIdx, lstrlen(szIdx), &rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}


//오브젝트 뿌리기
	for( list<POBJECT>::iterator iter = m_listObject.begin(); iter != m_listObject.end(); ++iter)
	{
		float		fX = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();
		float		fY = CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec();

		(*iter)->iX -= fX;
		(*iter)->iY -= fY;

		///맵툴에서 좌표 이상하게 잡는 바람에 이렇게 설정...;;
		D3DXMatrixTranslation(&matTrans, (*iter)->iX  - 200
			, (*iter)->iY - 300, 0.f);

		m_Info.matWorld = matTrans;

		m_Info.vCenter = D3DXVECTOR3(160.f / 2.f, 80.f / 2.0f, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_Info.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(CTextureMgr::GetInstance()->GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_OBJECT, (*iter)->iDrawID)
			, NULL, &m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}
//dat를 읽어왔는데 다시 읽어오려고 하니깐 화면이 안 뜨는듯
void CBackGround::InitTile(void)
{
	HANDLE			hFile;
	DWORD			dwByte;

	hFile = CreateFile(L"../Data/Act1/act1.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING
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
	//닫아줘야 나중에 다시 로드할때 이어서 읽지 않는다
	//만약 닫지 않아 이어서 읽게 된다면 앞에서 읽었던 유효한 범위 이후부터 다시 읽기 때문에 타일이나 오브젝트 정보가 안읽혀진다
	CloseHandle(hFile);
}

bool CBackGround::CollsionPtoT(int iIndex, POINT PlayerPos)
{
	int tilesizex = 160, tilesizey = 80;

	float	fGrad = (tilesizey / 2.f) / (tilesizex / 2.f);

	POINT		pt[4];
	// 왼쪽
	pt[0].x = long(m_vecTile[iIndex]->iX - tilesizex / 2);
	pt[0].y = long(m_vecTile[iIndex]->iY);

	// 위쪽
	pt[1].x = long(m_vecTile[iIndex]->iX);
	pt[1].y = long(m_vecTile[iIndex]->iY + tilesizey / 2);

	// 오른쪽
	pt[2].x = long(m_vecTile[iIndex]->iX + tilesizex / 2);
	pt[2].y = long(m_vecTile[iIndex]->iY);

	// 아래쪽
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
void CBackGround::Release( void )
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

CObj* CBackGround::Clone( void )
{
	return new CBackGround(*this);
}
