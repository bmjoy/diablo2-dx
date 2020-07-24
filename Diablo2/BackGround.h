#pragma once
#include "obj.h"

class CBackGround :
	public CObj
{
private:
	vector<PTILE>		    m_vecTile;
	list<POBJECT>			m_listObject;

	int	m_iPlayerIdx; //�÷��̾ ���ִ� Ÿ������	
	POINT	PlayerPos; //�÷��̾� ��ǥ


public:
	const vector<PTILE>& GetTileInfo(void)
	{
		return m_vecTile;
	}

public:
	void InitTile(void); //Ÿ�� ������Ʈ ���� ����

	bool CollsionPtoT(int iIndex, POINT PlayerPos);

	//Ÿ���� x,y��ǥ ������
	D3DXVECTOR3 GetTilePos(int _Index) 
	{	
		D3DXVECTOR3 vecTarget;
		
		vecTarget.x = m_vecTile[_Index]->iX;
		vecTarget.y = m_vecTile[_Index]->iY;
		vecTarget.z = 0.f;
		
		return vecTarget;
	}
//			((CBackGround*)(CObjMgr::GetInstance()->GetObj(OBJECT_BACKGROUND,0)))->CollsionPtoT(num);
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CBackGround(void);
	CBackGround(const INFO& Info);
	~CBackGround(void);
};
