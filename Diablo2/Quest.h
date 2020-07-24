#pragma once
#include "interface.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "RectMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Defines.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "QuestMgr.h"

class CQuest :
	public CInterface
{
private:
	NEWRECT Q1;
	NEWRECT Q2;
	NEWRECT Q3;
	NEWRECT EXIT;

public:
	void MakeText(PTCHAR _pText, float _fX, float _fY);

	bool ShowQ1Note;
	bool ShowQ2Note;
	bool ShowQ3Note;

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual CObj* Clone(void);

public:
	CQuest(void);
	~CQuest(void);
};
