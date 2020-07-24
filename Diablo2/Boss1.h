#pragma once
#include "obj.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

#include "KeyMgr.h"
#include "Astar.h"

#include "ObjMgr.h"
#include "StateMgr.h"
#include "ScrollMgr.h"
#include "RectMgr.h"
#include "QuestMgr.h"

//액트1 보스
class CBoss1 :
	public CObj
{
private:
	float		m_fFrame;
	float		m_fDieTime; //죽는 모션 보여주는 1초 
	float		m_fDieEndTime; //몹 시체 보여주고 지우는 1초
	float		m_fAstarTick; //astar 부하 줄이기위해
	float		m_fDistance; //유저와의 거리
	int			m_iStateID;
	int			m_iMaxCnt;

	D3DXMATRIX		matTrans;
	D3DXVECTOR3 m_vPlayerPos;//유저의 위치
	
	bool DieTimeCount; //죽는모션 -> 죽은 상태로 넘어가는 카운트
	bool DieCheck;		//죽은상태에서 1초정도 지난 다음에 지우기 위한 bool값
	
	POINT PlayerScroll;
	CObj* m_pPlayer;

	//타일 정보를 얻어오자 ( 마우스가 선택한 타일의 인덱스, 플레이어가 서있는곳의 인덱스를 얻기위해)
	vector<PTILE>		m_vecTile;
	list<int> m_BestList;
	bool CollisionMtoT(int iIndex, POINT ptMouse);

public:
	void AStarMove(void); //유저 때려잡으러 가기
	void Move(float m_fAngle); //걷기
	void Stand(float m_fAngle); //서있기
	void Attack(float m_fAngle);//공격
	void Hit(float m_fAngle); //얻어맞기
	void die(void); //죽기
	void RunToStand(void); //가다 멈추기
	void DistanceChk(void); //유저와의 거리 체크
	void Pattern(void); //각종 모션 조건
	
	bool GetDieCheck(void) { return DieCheck; } //objmgr에서 죽었는지 안죽었는지 체크용

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);

public:
	CBoss1(void);
	virtual ~CBoss1(void);
};
