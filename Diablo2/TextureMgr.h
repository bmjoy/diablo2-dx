#pragma once

#include "Defines.h"
#include "SingleTon.h"
#include "Texture.h"


// 이미지를 로드한다.
// 로드한 이미지를 저장한다.
// 이미지를 보내준다.

//#Study
//이곳에는 실제 이미지는 없고
//멀티 , 싱글 텍스쳐 타입별 객체를 갖고있는다
// 싱글 => LPDIRECT3DTEXTURE9 하나만
// 멀티 => multimap<int, vector<LPDIRECT3DTEXTURE9>> 이런식으로 여러개
class CTextureMgr
	: public CSingleTon<CTextureMgr>
{
private:
	// 이미지를 저장하기위한 컨테이너를 선언한다.
	multimap<int, CTexture*>		m_mapTex;

public:
	void AddTexture(PTCHAR pFileName, TEXTYPE Textype, int iObjID
		, int iStateID = 0, int iCnt = 0); // (파일경로, 멀티or싱글, 객체구분, 객체상태구분, 몇장)
public:
//					객체구분				객체상태						몇번째장?
//GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
/*
#구조

	m_mapTex<OBJECT_BACKGROUND,CMultiTexture>
	부모 CTexture 안에는 이렇게 되어있다 

	1.CSingleTexture
	LPDIRECT3DTEXTURE9		m_pTex;
	
	2.CMultiTexture
	multimap<int, vector<LPDIRECT3DTEXTURE9>>		m_MapTex;

*/
	LPDIRECT3DTEXTURE9 GetTexture(int iObjID, int iStateID = 0, int iCnt = 0)
	{
		multimap<int, CTexture*>::iterator	iter = m_mapTex.find(iObjID);

		if(iter == m_mapTex.end())
		{
			ERRORCHK(L"텍스쳐가 없습니다!");
			return NULL;
		}

		return iter->second->GetTexture(iStateID, iCnt);
	}

	void Release(void);

	friend CTextureMgr* CSingleTon<CTextureMgr>::GetInstance();
private:
	CTextureMgr(void);
public:
	~CTextureMgr(void);
};
