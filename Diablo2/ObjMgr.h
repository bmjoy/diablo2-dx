#pragma once

#include "Defines.h"
#include "SingleTon.h"
#include "Obj.h"
#include "ObjProto.h"
#include "BackGround.h"
#include "QuestMgr.h"

class CObjMgr
	: public CSingleTon<CObjMgr>
{
private:
	//어떤 state든지 모든 오브젝트들은 여기 들어간다
	map<int, list<CObj*>>			m_MapObj;
public:
	const vector<PTILE>& GetTileInfo(void)
	{
		//Study
		//map<int, list<CObj*>>::iterator	iter = m_MapObj.find(OBJECT_BACKGROUND);

		//OBJECT_BACKGROUND 와 OBJECT_BACKGROUND
		//왜 둘중 아무거나 넣어도 되는걸까 
		//어차피 백그라운드들 enum이 0 이라서
		//리턴값은 계속 m_MapObj의 0번에 있는 것이 나가기 때문

		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(OBJECT_BACKGROUND);

		if(iter == m_MapObj.end())
		{
			ERRORCHK(L"타일을을 가져올 객체가 읍다");			
		}

		else
		{
			return ((CBackGround*)iter->second.front())->GetTileInfo();
		}
	}
	const INFO& GetInfo(int iObjID, int iCnt = 0)
	{
		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(iObjID);

		if(iter == m_MapObj.end())
		{
			ERRORCHK(L"가져오려는 객체가 없음.");
		}	
		else
		{
			list<CObj*>::iterator iter1 = iter->second.begin();

			for (int i = 0; i < iCnt; ++i)
			{
				++iter1;
			}
			return (*iter1)->GetInfo();
		}	
	}

	CObj*		GetObj(int iObjID,int Cnt);

	float m_fTick;

	void ClickMonster(void); //클릭해서 이게 몬스터인지 식별
	void SetDirMotion(float fX, float fY); //바라보는 방향, 공격
public:
	void Progress(void);
	void Render(void);
	void Release(void);

public:

//Study #1
/*
AddObject(OBJECT_BACKGROUND, m_pObjProto);

pObj = pProto->GetProto(iObjKey)->Clone();

//OBJECT_BACKGROUND 찾아서 미리 만들어놓은 프로토타입을 뱉는다

CObj* GetProto(int iObjKey)
{
	map<int, CObj*>::iterator	iter = m_mapObj.find(iObjKey);
	if(iter == m_mapObj.end())				
		return NULL;		
	return iter->second;
}
*/
//Study #2
/*
1.결국 여러마리 넣을 몬스터들 빼면
2.대부분 m_MapObj의 key값별 list당 오브젝트들은 하나씩만 있다...
  map하나에 여러 list을 묶어놓은셈
*/
	inline void AddObject(int iObjKey, CObjProto* pProto)
	{
		CObj*		pObj = NULL;

		//미리 만들어놓은 프로토타입을 복제한다
		pObj = pProto->GetProto(iObjKey)->Clone();

		if(pObj == NULL)
		{
			ERRORCHK(L"원형객체를 못가져왔당");
			return;
		}
		pObj->Initialize();

		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(iObjKey);

		if(iter == m_MapObj.end()) //없으면 새로만들고
		{
			list<CObj*>		ObjList;
			ObjList.push_back(pObj);
			m_MapObj.insert(make_pair(iObjKey, ObjList));
		}
		else //있으면 거기 key값을 가진 리스트에 넣고
			iter->second.push_back(pObj);
	}

	//좌표지정 AddObject(몹 뿌리기용)
	inline void AddObject(int iObjKey, CObjProto* pProto, float fX, float fY)
	{
		CObj*		pObj = NULL;

		//미리 만들어놓은 프로토타입을 복제한다
		pObj = pProto->GetProto(iObjKey)->Clone();

		if(pObj == NULL)
		{
			ERRORCHK(L"원형객체를 못가져왔당");
			return;
		}
		pObj->Initialize(); //몹들은 ini를 할때 좌표를 매개변수로 받아서 한다
		pObj->SetRegenPos(fX,fY);

		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(iObjKey);

		if(iter == m_MapObj.end()) //없으면 새로만들고
		{
			list<CObj*>		ObjList;
			ObjList.push_back(pObj);
			m_MapObj.insert(make_pair(iObjKey, ObjList));
		}
		else //있으면 거기 key값을 가진 리스트에 넣고
			iter->second.push_back(pObj);
	}

public:
	friend CObjMgr* CSingleTon<CObjMgr>::GetInstance();
private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};
