#pragma once

#include "Texture.h"

class CSingleTexture
	: public CTexture
{
private: // �̹��� ����� ��ü
	LPDIRECT3DTEXTURE9		m_pTex;
	
public:
	virtual void LoadTexture(PTCHAR pFileName, int iStateID = 0, int iCnt = 0);
	virtual LPDIRECT3DTEXTURE9 GetTexture(int iStateID = 0, int iCnt = 0)
	{
		return m_pTex;
	}

	virtual void Release(void);
public:
	CSingleTexture(void);
	~CSingleTexture(void);
};
