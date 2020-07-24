#pragma once
#include "singleton.h"
#include "stdlib.h"
#include "time.h"

class CRandomMgr :
	public CSingleTon<CRandomMgr>
{
public:
	int Random(int min, int max)
		{
			srand((unsigned)time(NULL));
			int a = (rand() % (max-min+1)) + min;	

		 return a;
		}

public:
	friend CRandomMgr* CSingleTon<CRandomMgr>::GetInstance();
public:
	CRandomMgr(void);
	~CRandomMgr(void);
};


