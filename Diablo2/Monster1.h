#pragma once
#include "obj.h"
#include "QuestMgr.h"
//��Ʈ1 ����1(ī��)
class CMonster1 :
	public CObj
{
private:
	float		m_fFrame;
	float		m_fDieTime; //�״� ��� �����ִ� 1�� 
	float		m_fDieEndTime; //�� ��ü �����ְ� ����� 1��
	float		m_fAstarTick; //astar ���� ���̱�����
	float m_fDistance; //�������� �Ÿ�
	int			m_iStateID;
	int			m_iMaxCnt;

	D3DXMATRIX		matTrans;
	D3DXVECTOR3 m_vPlayerPos;//������ ��ġ
	
	bool DieTimeCount; //�״¸�� -> ���� ���·� �Ѿ�� ī��Ʈ
	bool DieCheck;		//�������¿��� 1������ ���� ������ ����� ���� bool��
	
	POINT PlayerScroll;
	CObj* m_pPlayer;

	//Ÿ�� ������ ������ ( ���콺�� ������ Ÿ���� �ε���, �÷��̾ ���ִ°��� �ε����� �������)
	vector<PTILE>		m_vecTile;
	list<int> m_BestList;
	bool CollisionMtoT(int iIndex, POINT ptMouse);

public:
	void AStarMove(void); //���� ���������� ����
	void Move(float m_fAngle); //�ȱ�
	void Stand(float m_fAngle); //���ֱ�
	void Attack(float m_fAngle);//����
	void Hit(float m_fAngle); //���±�
	void die(void); //�ױ�
	void RunToStand(void); //���� ���߱�
	void DistanceChk(void); //�������� �Ÿ� üũ
	void Pattern(void); //���� ��� ����
	
	bool GetDieCheck(void) { return DieCheck; } //objmgr���� �׾����� ���׾����� üũ��


public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);
public:
	CMonster1(void);
	CMonster1(const INFO& Info);
	virtual ~CMonster1(void);
};
