#include "StdAfx.h"
#include "TextureMgr.h"

#include "SingleTexture.h"
#include "MultiTexture.h"

CTextureMgr::CTextureMgr(void)
{
}

CTextureMgr::~CTextureMgr(void)
{
	Release();
}
//Study
//AddTexture(L"../Texture/Tile/Tile0%d.png", TEXTYPE_MULTI, OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, TILENUM);
//
void CTextureMgr::AddTexture(PTCHAR pFileName, TEXTYPE Textype, int iObjID, int iStateID, int iCnt)
{
	CTexture*		pTexture = NULL;

	multimap<int, CTexture*>::iterator	iter = m_mapTex.find(iObjID);

	if(iter == m_mapTex.end())
	{
		switch(Textype)
		{
		case TEXTYPE_SINGLE:
			pTexture = new CSingleTexture;
			break;


		case TEXTYPE_MULTI:
			pTexture = new CMultiTexture;
			break;
		}
		//Study #3
		//위에서 pTexture 타입이 정해져서 알아서 찾아감
		pTexture->LoadTexture(pFileName, iStateID, iCnt);

		m_mapTex.insert(make_pair(iObjID, pTexture));
	}

	else
		iter->second->LoadTexture(pFileName, iStateID, iCnt);
		
}

void CTextureMgr::Release(void)
{
	for (multimap<int, CTexture*>::iterator	iter = m_mapTex.begin();
		iter != m_mapTex.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapTex.clear();

}