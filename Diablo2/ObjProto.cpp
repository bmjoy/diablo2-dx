#include "StdAfx.h"
#include "ObjProto.h"

CObjProto::CObjProto(void)
{
}

CObjProto::~CObjProto(void)
{
	Release();
}

void CObjProto::Release( void )
{
	for(map<int, CObj*>::iterator	iter = m_mapObj.begin();
		iter != m_mapObj.end(); ++iter)
	{
		SAFE_DELETE(iter->second);		
	}
	m_mapObj.clear();

}
