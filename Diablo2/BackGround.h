#pragma once
#include "obj.h"

class CBackGround :
	public CObj
{
private:
	vector<PTILE>		    m_vecTile;
	list<POBJECT>			m_listObject;

	int	m_iPlayerIdx; //플레이어가 서있는 타일정보	
	POINT	PlayerPos; //플레이어 좌표


public:
	const vector<PTILE>& GetTileInfo(void)
	{
		return m_vecTile;
	}

public:
	void InitTile(void); //타일 오브젝트 정보 읽음

	bool CollsionPtoT(int iIndex, POINT PlayerPos);

	//타일의 x,y좌표 따오기
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
