#pragma once

#include "Defines.h"
#include "SingleTon.h"

class CAStar
	: public CSingleTon<CAStar>
{
private:
	///나중에 cost대로 정렬해야 하니깐
	multimap<float, PNODE>			m_OpenList; // 조사대상 타일을들을 모아놓는 객체
	multimap<float, PNODE>			m_CloseList; // 조사한 타일을들 모아놓는다.
	list<int>			m_BestList; // 최종경로

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
