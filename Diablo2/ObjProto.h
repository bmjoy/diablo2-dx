#pragma once

#include "Defines.h"
#include "Obj.h"

class CObjProto
{
protected:
	//#Study
	//� ��ü�� ���鶧 �׻� ������Ÿ�� �����̳ʿ� �ִ����� �����شٰ� ����
	// ������ü���� �����ϱ����� �����̳�.
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
