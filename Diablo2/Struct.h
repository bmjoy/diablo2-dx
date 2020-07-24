#pragma once

typedef struct tagInfo
{
	// 위치 
	// 벡터	
	D3DXVECTOR3		vPos;

	// 움직여야할 방, 길이
	D3DXVECTOR3		vDir;

	// 0도방향을 바보는 벡터.
	D3DXVECTOR3		vLook;

	// 출력하고자하이미지의 중심
	D3DXVECTOR3		vCenter;

	// 모든 상태를 지고 있는 행렬
	D3DXMATRIX		matWorld;

	D3DXMATRIX		matTrans;

}INFO, *PINFO;

typedef struct tagstatus
{
	//캐릭터의 피,마나,공격력,방어력,이동속도,보고있는각도
	int iHp;
	int iMaxHp;
	int iMana;
	int iMaxMana;
	int iAtk;
	int iDef;
	//이동관련
	float fAngle;
	float fAngleNum; //11.25
	int Now;
	int Goal;
	int Str;
	int Dex;
	int Int;
	int Vit;
	int Lv;

}STATUS, *PSTATUS;

typedef struct tagrectinfo
{
	float fX; //렉트의중점
	float fY;
	float fSizeX; //렉트사이즈
	float fSizeY;
}NEWRECT, *PNEWRECT;


typedef struct tagNode
{
	float		fTCost;	// 부모노드까지의 거리 + 골지점까지의거리
	float		fPCost;	// 부모노드까지의 거리
	float		fGCost;	// 골지점까지의거리
	int			iIndex; // 타일 번호
	tagNode*	pParent; // 현재 조사하는 타일의 부모
}NODE, *PNODE;

typedef struct tagTile
{
	float			iX, iY; //이거 맵툴에도 적용해야함
	int			iSizeX, iSizeY;
	// 벡터에 이미지들을 모아놓을것이다.
	// 그 벡터에 있는 이미지중에 어떤걸 사용해서 타일을 표현할건지..
	int			iDrawID; 
	BYTE		byOption;
}TILE, *PTILE;

typedef struct tagObject
{
	float		iX, iY;
	int			iSizeX, iSizeY;
	int			iDrawID; 
	BYTE		byOption;
}OBJECT, *POBJECT;
