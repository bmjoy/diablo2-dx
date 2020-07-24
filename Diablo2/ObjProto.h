#pragma once

#include "Defines.h"
#include "Obj.h"

class CObjProto
{
protected:
	//#Study
	//어떤 객체를 만들때 항상 프로토타입 컨테이너에 있던것을 복제해다가 쓰자
	// 원형객체들을 보관하기위한 컨테이너.
	map<int, CObj*>			m_mapObj;
public:
	CObj* GetProto(int iObjKey)
	{
		map<int, CObj*>::iterator	iter = m_mapObj.find(iObjKey);
		if(iter == m_mapObj.end())				
			return NULL;		
		return iter->second;
	}

public:
	virtual void SetProto(void)PURE;
	virtual void Release(void);

public:
	CObjProto(void);
	virtual ~CObjProto(void);
};
