#pragma once

#include "Defines.h"
#include "Texture.h"

class CMultiTexture
	: public CTexture
{
private:
	multimap<int, vector<LPDIRECT3DTEXTURE9>>		m_MapTex;
public:
	virtual void LoadTexture(PTCHAR pFileName, int iStateID = 0, int iCnt = 0);
	virtual LPDIRECT3DTEXTURE9 GetTexture(int iStateID = 0, int iCnt = 0)
	{
		multimap<int, vector<LPDIRECT3DTEXTURE9>>::iterator iter = m_MapTex.find(iStateID);

		if(iter == m_MapTex.end())
		{
			ERRORCHK(L"니가 차즌ㄴ게 없어");
			return NULL;
		}
		return iter->second[iCnt];
	}
	virtual void Release(void);
public:
	CMultiTexture(void);
	~CMultiTexture(void);
};
