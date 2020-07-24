#include "StdAfx.h"
#include "AStar.h"

#include "ObjMgr.h"

CAStar::CAStar(void)
{
}

CAStar::~CAStar(void)
{
	Release();
}


const list<int>& CAStar::AStarStart(int iStartIdx, int iEndIdx)
{
	Release();

	if(iStartIdx == iEndIdx)
		return m_BestList;

	m_vecTile = CObjMgr::GetInstance()->GetTileInfo();

	if(m_vecTile[iEndIdx]->byOption == 1)
		return m_BestList;

	m_iStartIdx = iStartIdx;
	m_iEndIdx = iEndIdx;

	return MakeBestList();
}

const list<int>& CAStar::MakeBestList(void)
{
	PNODE		pParent = MakeParent();

	// 주위 여덟개를 조사하자.
	// 조사해서 갈수 있는 타일이면 오픈리스트에 추가하자.
	PNODE		pNode = NULL; // 오픈리스트에 추가할 노드포인터


	while(true)
	{
		// 위
		// 위의 타일을 오픈리스트에 추가한다.
		int		iIndex = pParent->iIndex - ACT1_TILEX * 2;

		if(pParent->iIndex >= ACT1_TILEX * 2 // 40번보다 큰애들만 위에 타일이 존재한다
			&& m_vecTile[iIndex]->byOption == 0 // 갈 수 있는 타일이냐 아니냐?
			&& CheckList(iIndex)) // OpenList에 이미 들어간것이나 CloseList에 보내진것은 검사하지 않는다
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// 오른쪽위
		iIndex = pParent->iIndex - (ACT1_TILEX - (pParent->iIndex / ACT1_TILEX) % 2);
			
		if(pParent->iIndex >= ACT1_TILEX
			&& pParent->iIndex % (ACT1_TILEX * 2) != ACT1_TILEX * 2 - 1
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// 오른쪽
		iIndex = pParent->iIndex + 1;

		if((pParent->iIndex + 1) % ACT1_TILEX != 0			
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// 오른쪽아래
		iIndex = pParent->iIndex + (ACT1_TILEX + (pParent->iIndex / ACT1_TILEX) % 2);

		if(pParent->iIndex < ACT1_TILEX * ACT1_TILEY - ACT1_TILEX 
			&& pParent->iIndex % (ACT1_TILEX * 2) != ACT1_TILEX * 2 - 1
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}


		// 아래
		iIndex = pParent->iIndex + ACT1_TILEX * 2;

		if(pParent->iIndex < ACT1_TILEX * ACT1_TILEY - ACT1_TILEX * 2			
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// 왼쪽아래
		iIndex = pParent->iIndex + (ACT1_TILEX - 1 + (pParent->iIndex / ACT1_TILEX) % 2);

		if(pParent->iIndex % (ACT1_TILEX * 2) != 0
			&& pParent->iIndex < ACT1_TILEX * ACT1_TILEY - ACT1_TILEX
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}
		
		// 왼쪽
		iIndex = pParent->iIndex - 1;

		if((pParent->iIndex % ACT1_TILEX) != 0			
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		
		// 왼쪽위
		iIndex = pParent->iIndex - (ACT1_TILEX + 1 - (pParent->iIndex / ACT1_TILEX) % 2);

		if(pParent->iIndex % (ACT1_TILEX * 2) != 0
			&& pParent->iIndex >= ACT1_TILEX
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}
		// 조건 끝!

		// 오픈리스트 완성
		// m_OpenList를 정렬해야지 비용이 가장 작은넘을 찾는다.
		// 가장 작은놈을 m_CloseList에 추가.
		// m_OpenList에서 가장 작은놈을 삭제
		// pParent = 가장 작은 놈, 이놈을 기준으로 다시 주변검색
		
		multimap<float, PNODE>	::iterator iter = m_OpenList.begin(); 
		pParent = iter->second; //multimap은 가장 작은값이 맨 위에 있다

		m_CloseList.insert(make_pair(pParent->fTCost,pParent));//방문했던 리스트를 closelist에 이동

		iter = m_OpenList.erase(iter); //openlist 지우기, 다음 경로를 찾기위해 비워둔다

		if(pParent->iIndex == m_iEndIdx)
		{
			while(true)
			{
				m_BestList.push_front(pParent->iIndex);
				pParent = pParent->pParent; //부모의 부모를 계속 리스트에 추가(가장 비용이 적어 뽑혔던 것들)
				// 스타트까지 오면 모든 루프 탈출.
				if(pParent->pParent == NULL)
				{
					return m_BestList;
				}
			}
		}
	}
//+		+		m_BestList	[6](62,63,103,143,142,182)	std::list<int,std::allocator<int> >




	
	//pParent
}

PNODE	CAStar::CreateNode(int iIndex, PNODE pParent)
{
	PNODE	pNode = new NODE;

	// 조사하는 노드와 부모노드까지의 거리.

	float	fWidth = m_vecTile[iIndex]->iX - m_vecTile[pParent->iIndex]->iX;
	float	fHeight = m_vecTile[iIndex]->iY - m_vecTile[pParent->iIndex]->iY;
	
	float	fPCost = sqrtf(fHeight * fHeight + fWidth * fWidth);

	// 조사하는 노드와 목표노드까지의 거리.

	fWidth = m_vecTile[iIndex]->iX - m_vecTile[m_iEndIdx]->iX;
	fHeight = m_vecTile[iIndex]->iY - m_vecTile[m_iEndIdx]->iY;

	float fGCost = sqrtf(fWidth * fWidth + fHeight * fHeight);	

	pNode->fTCost = fPCost + fGCost; 

	pNode->iIndex = iIndex;
	pNode->pParent = pParent;
	return pNode;
}

bool CAStar::CheckList(int iIndex)
{
	for (multimap<float, PNODE>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		if(iter->second->iIndex == iIndex)
			return false;
	}

	for (multimap<float, PNODE>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		if(iter->second->iIndex == iIndex)
			return false;
	}
	return true;
}

PNODE CAStar::MakeParent(void)
{
	PNODE		pParent = new NODE;

	pParent->fTCost = 0.f;
	pParent->fPCost = 0.f;
	pParent->fGCost = 0.f;
	
	pParent->iIndex = m_iStartIdx;
	pParent->pParent = NULL;

	m_CloseList.insert(make_pair(pParent->fTCost, pParent));

	return pParent;
}

float CAStar::GetDisCost(int GoalIndex , int NowIndex)
{
	float fWidth = float(m_vecTile[NowIndex]->iX - m_vecTile[GoalIndex]->iX);
	float fHeight = float(m_vecTile[NowIndex]->iY - m_vecTile[GoalIndex]->iY);
	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);
	
	return fDistance;
}

void CAStar::Release(void)
{
	for (multimap<float, PNODE>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_OpenList.clear();

	for (multimap<float, PNODE>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_CloseList.clear();

	m_BestList.clear();
}