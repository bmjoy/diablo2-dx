#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
private:
	float		m_fFrame;
	int			m_iStateID;
	int			m_iMaxCnt;
	float		m_fAngle; // 플레이어가 보고있는 방향, 적용할 이미지 방향
	float		m_fAngleNum; // 11.25

	float		m_fRunTick; //뛰는소리

	int		Now;
	int		Goal;

	//맵의 실제좌표 뽑기용
	float	m_fInfoX;
	float	m_fInfoY;

	//astar 부하 줄이기 위해서
	bool	m_bClick;

public:
	void KeyInput(void);
	bool CollisionMtoT(int iIndex, POINT ptMouse);
	void  AStarMove(void);

	void PlayerMove(float m_fAngle); //캐릭터 움직이는 부분 넘 길어서...
	void PlayerStand(float m_fAngle); //마찬가지
	void PlayerAtk(float m_fAngle);
	void PlayerRunToStand(void);

	void ClearBestList(void) { m_BestList.clear(); }

	//타일 정보를 얻어오자 ( 마우스가 선택한 타일의 인덱스, 플레이어가 서있는곳의 인덱스를 얻기위해)
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
