#pragma once
#include "SingleTon.h"
#include "ObjMgr.h"
#include "TimeMgr.h"

class CScrollMgr :
	public CSingleTon<CScrollMgr>
{
private:
	POINT ScrollPT;
public:
	POINT GetScroll(void) 
	{
		ScrollPT.x = long(CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.x* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec());
		ScrollPT.y = long(CObjMgr::GetInstance()->GetInfo(OBJECT_PLAYER).vDir.y* PLAYER_SPEED * CTimeMgr::GetInstance()->GetPixelPerSec());	
		return ScrollPT;
	}
public:
	friend CScrollMgr* CSingleTon<CScrollMgr>::GetInstance();
public:
	CScrollMgr(void);
	~CScrollMgr(void);
};
