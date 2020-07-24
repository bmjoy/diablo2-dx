#pragma once

typedef struct tagInfo
{
	// ��ġ 
	// ����	
	D3DXVECTOR3		vPos;

	// ���������� ��, ����
	D3DXVECTOR3		vDir;

	// 0�������� �ٺ��� ����.
	D3DXVECTOR3		vLook;

	// ����ϰ������̹����� �߽�
	D3DXVECTOR3		vCenter;

	// ��� ���¸� ���� �ִ� ���
	D3DXMATRIX		matWorld;

	D3DXMATRIX		matTrans;

}INFO, *PINFO;

typedef struct tagstatus
{
	//ĳ������ ��,����,���ݷ�,����,�̵��ӵ�,�����ִ°���
	int iHp;
	int iMaxHp;
	int iMana;
	int iMaxMana;
	int iAtk;
	int iDef;
	//�̵�����
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
	float fX; //��Ʈ������
	float fY;
	float fSizeX; //��Ʈ������
	float fSizeY;
}NEWRECT, *PNEWRECT;


typedef struct tagNode
{
	float		fTCost;	// �θ�������� �Ÿ� + �����������ǰŸ�
	float		fPCost;	// �θ�������� �Ÿ�
	float		fGCost;	// �����������ǰŸ�
	int			iIndex; // Ÿ�� ��ȣ
	tagNode*	pParent; // ���� �����ϴ� Ÿ���� �θ�
}NODE, *PNODE;

typedef struct tagTile
{
	float			iX, iY; //�̰� �������� �����ؾ���
	int			iSizeX, iSizeY;
	// ���Ϳ� �̹������� ��Ƴ������̴�.
	// �� ���Ϳ� �ִ� �̹����߿� ��� ����ؼ� Ÿ���� ǥ���Ұ���..
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
