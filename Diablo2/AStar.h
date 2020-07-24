#pragma once

#include "Defines.h"
#include "SingleTon.h"

class CAStar
	: public CSingleTon<CAStar>
{
private:
	///���߿� cost��� �����ؾ� �ϴϱ�
	multimap<float, PNODE>			m_OpenList; // ������ Ÿ�������� ��Ƴ��� ��ü
	multimap<float, PNODE>			m_CloseList; // ������ Ÿ������ ��Ƴ��´�.
	list<int>			m_BestList; // �������

	vector<PTILE>		m_vecTile;

	int					m_iStartIdx, m_iEndIdx;

public:
	PNODE	CreateNode(int iIndex, PNODE pNode);
	bool CheckList(int iIndex);
	PNODE MakeParent(void);
	const list<int>& AStarStart(int iStartIdx, int iEndIdx);
	const list<int>& MakeBestList(void);
	
	void Release(void);

	float GetDisCost(int GoalIndex, int NowIndex);
	list<int> GetBestList(void) { return m_BestList; }

	friend CAStar* CSingleTon<CAStar>::GetInstance();
private:
	CAStar(void);
public:
	~CAStar(void);
};
