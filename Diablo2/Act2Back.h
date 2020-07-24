#pragma once
#include "obj.h"

class CAct2Back :
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
	void InitTile(void);
	void  PlayerOnTile(void);
	bool CollsionPtoT(int iIndex, POINT PlayerPos);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CAct2Back(void);
	CAct2Back(const INFO& Info);
	~CAct2Back(void);
};
