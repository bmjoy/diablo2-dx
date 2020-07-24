#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
private:
	float		m_fFrame;
	int			m_iStateID;
	int			m_iMaxCnt;
	float		m_fAngle; // �÷��̾ �����ִ� ����, ������ �̹��� ����
	float		m_fAngleNum; // 11.25

	float		m_fRunTick; //�ٴ¼Ҹ�

	int		Now;
	int		Goal;

	//���� ������ǥ �̱��
	float	m_fInfoX;
	float	m_fInfoY;

	//astar ���� ���̱� ���ؼ�
	bool	m_bClick;

public:
	void KeyInput(void);
	bool CollisionMtoT(int iIndex, POINT ptMouse);
	void  AStarMove(void);

	void PlayerMove(float m_fAngle); //ĳ���� �����̴� �κ� �� ��...
	void PlayerStand(float m_fAngle); //��������
	void PlayerAtk(float m_fAngle);
	void PlayerRunToStand(void);

	void ClearBestList(void) { m_BestList.clear(); }

	//Ÿ�� ������ ������ ( ���콺�� ������ Ÿ���� �ε���, �÷��̾ ���ִ°��� �ε����� �������)
	vector<PTILE>		m_vecTile;
	list<int> m_BestList;

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CPlayer(void);
	CPlayer(const INFO& Info);
	~CPlayer(void);
};
