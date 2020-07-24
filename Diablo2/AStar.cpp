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

	// ���� �������� ��������.
	// �����ؼ� ���� �ִ� Ÿ���̸� ���¸���Ʈ�� �߰�����.
	PNODE		pNode = NULL; // ���¸���Ʈ�� �߰��� ���������


	while(true)
	{
		// ��
		// ���� Ÿ���� ���¸���Ʈ�� �߰��Ѵ�.
		int		iIndex = pParent->iIndex - ACT1_TILEX * 2;

		if(pParent->iIndex >= ACT1_TILEX * 2 // 40������ ū�ֵ鸸 ���� Ÿ���� �����Ѵ�
			&& m_vecTile[iIndex]->byOption == 0 // �� �� �ִ� Ÿ���̳� �ƴϳ�?
			&& CheckList(iIndex)) // OpenList�� �̹� �����̳� CloseList�� ���������� �˻����� �ʴ´�
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// ��������
		iIndex = pParent->iIndex - (ACT1_TILEX - (pParent->iIndex / ACT1_TILEX) % 2);
			
		if(pParent->iIndex >= ACT1_TILEX
			&& pParent->iIndex % (ACT1_TILEX * 2) != ACT1_TILEX * 2 - 1
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// ������
		iIndex = pParent->iIndex + 1;

		if((pParent->iIndex + 1) % ACT1_TILEX != 0			
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// �����ʾƷ�
		iIndex = pParent->iIndex + (ACT1_TILEX + (pParent->iIndex / ACT1_TILEX) % 2);

		if(pParent->iIndex < ACT1_TILEX * ACT1_TILEY - ACT1_TILEX 
			&& pParent->iIndex % (ACT1_TILEX * 2) != ACT1_TILEX * 2 - 1
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}


		// �Ʒ�
		iIndex = pParent->iIndex + ACT1_TILEX * 2;

		if(pParent->iIndex < ACT1_TILEX * ACT1_TILEY - ACT1_TILEX * 2			
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		// ���ʾƷ�
		iIndex = pParent->iIndex + (ACT1_TILEX - 1 + (pParent->iIndex / ACT1_TILEX) % 2);

		if(pParent->iIndex % (ACT1_TILEX * 2) != 0
			&& pParent->iIndex < ACT1_TILEX * ACT1_TILEY - ACT1_TILEX
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}
		
		// ����
		iIndex = pParent->iIndex - 1;

		if((pParent->iIndex % ACT1_TILEX) != 0			
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}

		
		// ������
		iIndex = pParent->iIndex - (ACT1_TILEX + 1 - (pParent->iIndex / ACT1_TILEX) % 2);

		if(pParent->iIndex % (ACT1_TILEX * 2) != 0
			&& pParent->iIndex >= ACT1_TILEX
			&& m_vecTile[iIndex]->byOption == 0
			&& CheckList(iIndex))
		{
			pNode = CreateNode(iIndex, pParent);
			m_OpenList.insert(make_pair(pNode->fTCost, pNode));
		}
		// ���� ��!

		// ���¸���Ʈ �ϼ�
		// m_OpenList�� �����ؾ��� ����� ���� �������� ã�´�.
		// ���� �������� m_CloseList�� �߰�.
		// m_OpenList���� ���� �������� ����
		// pParent = ���� ���� ��, �̳��� �������� �ٽ� �ֺ��˻�
		
		multimap<float, PNODE>	::iterator iter = m_OpenList.begin(); 
		pParent = iter->second; //multimap�� ���� �������� �� ���� �ִ�

		m_CloseList.insert(make_pair(pParent->fTCost,pParent));//�湮�ߴ� ����Ʈ�� closelist�� �̵�

		iter = m_OpenList.erase(iter); //openlist �����, ���� ��θ� ã������ ����д�

		if(pParent->iIndex == m_iEndIdx)
		{
			while(true)
			{
				m_BestList.push_front(pParent->iIndex);
				pParent = pParent->pParent; //�θ��� �θ� ��� ����Ʈ�� �߰�(���� ����� ���� ������ �͵�)
				// ��ŸƮ���� ���� ��� ���� Ż��.
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

	// �����ϴ� ���� �θ�������� �Ÿ�.

	float	fWidth = m_vecTile[iIndex]->iX - m_vecTile[pParent->iIndex]->iX;
	float	fHeight = m_vecTile[iIndex]->iY - m_vecTile[pParent->iIndex]->iY;
	
	float	fPCost = sqrtf(fHeight * fHeight + fWidth * fWidth);

	// �����ϴ� ���� ��ǥ�������� �Ÿ�.

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