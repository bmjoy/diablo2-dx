#pragma once
#include "singleton.h"
#include "Defines.h"
#include "ObjMgr.h"
class CRenderMgr :
	public CSingleTon<CRenderMgr>
{
private:
	multimap<float,CObj*>	m_YposRender;

public:
	void Render(void);		
	void ArrayYpos(map<int,list<CObj*>>* _YSortMap);


public:
	friend CRenderMgr* CSingleTon<CRenderMgr>::GetInstance();
private:
	CRenderMgr(void);
public:
	~CRenderMgr(void);
};
