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
	//� state���� ��� ������Ʈ���� ���� ����
	map<int, list<CObj*>>			m_MapObj;
public:
	const vector<PTILE>& GetTileInfo(void)
	{
		//Study
		//map<int, list<CObj*>>::iterator	iter = m_MapObj.find(OBJECT_BACKGROUND);

		//OBJECT_BACKGROUND �� OBJECT_BACKGROUND
		//�� ���� �ƹ��ų� �־ �Ǵ°ɱ� 
		//������ ��׶���� enum�� 0 �̶�
		//���ϰ��� ��� m_MapObj�� 0���� �ִ� ���� ������ ����

		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(OBJECT_BACKGROUND);

		if(iter == m_MapObj.end())
		{
			ERRORCHK(L"Ÿ������ ������ ��ü�� ����");			
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
			ERRORCHK(L"���������� ��ü�� ����.");
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

	void ClickMonster(void); //Ŭ���ؼ� �̰� �������� �ĺ�
	void SetDirMotion(float fX, float fY); //�ٶ󺸴� ����, ����
public:
	void Progress(void);
	void Render(void);
	void Release(void);

public:

//Study #1
/*
AddObject(OBJECT_BACKGROUND, m_pObjProto);

pObj = pProto->GetProto(iObjKey)->Clone();

//OBJECT_BACKGROUND ã�Ƽ� �̸� �������� ������Ÿ���� ��´�

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
1.�ᱹ �������� ���� ���͵� ����
2.��κ� m_MapObj�� key���� list�� ������Ʈ���� �ϳ����� �ִ�...
  map�ϳ��� ���� list�� ���������
*/
	inline void AddObject(int iObjKey, CObjProto* pProto)
	{
		CObj*		pObj = NULL;

		//�̸� �������� ������Ÿ���� �����Ѵ�
		pObj = pProto->GetProto(iObjKey)->Clone();

		if(pObj == NULL)
		{
			ERRORCHK(L"������ü�� �������Դ�");
			return;
		}
		pObj->Initialize();

		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(iObjKey);

		if(iter == m_MapObj.end()) //������ ���θ����
		{
			list<CObj*>		ObjList;
			ObjList.push_back(pObj);
			m_MapObj.insert(make_pair(iObjKey, ObjList));
		}
		else //������ �ű� key���� ���� ����Ʈ�� �ְ�
			iter->second.push_back(pObj);
	}

	//��ǥ���� AddObject(�� �Ѹ����)
	inline void AddObject(int iObjKey, CObjProto* pProto, float fX, float fY)
	{
		CObj*		pObj = NULL;

		//�̸� �������� ������Ÿ���� �����Ѵ�
		pObj = pProto->GetProto(iObjKey)->Clone();

		if(pObj == NULL)
		{
			ERRORCHK(L"������ü�� �������Դ�");
			return;
		}
		pObj->Initialize(); //������ ini�� �Ҷ� ��ǥ�� �Ű������� �޾Ƽ� �Ѵ�
		pObj->SetRegenPos(fX,fY);

		map<int, list<CObj*>>::iterator	iter = m_MapObj.find(iObjKey);

		if(iter == m_MapObj.end()) //������ ���θ����
		{
			list<CObj*>		ObjList;
			ObjList.push_back(pObj);
			m_MapObj.insert(make_pair(iObjKey, ObjList));
		}
		else //������ �ű� key���� ���� ����Ʈ�� �ְ�
			iter->second.push_back(pObj);
	}

public:
	friend CObjMgr* CSingleTon<CObjMgr>::GetInstance();
private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};
