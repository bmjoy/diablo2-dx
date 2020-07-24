#pragma once

#include "Defines.h"
#include "SingleTon.h"
#include "Texture.h"


// �̹����� �ε��Ѵ�.
// �ε��� �̹����� �����Ѵ�.
// �̹����� �����ش�.

//#Study
//�̰����� ���� �̹����� ����
//��Ƽ , �̱� �ؽ��� Ÿ�Ժ� ��ü�� �����ִ´�
// �̱� => LPDIRECT3DTEXTURE9 �ϳ���
// ��Ƽ => multimap<int, vector<LPDIRECT3DTEXTURE9>> �̷������� ������
class CTextureMgr
	: public CSingleTon<CTextureMgr>
{
private:
	// �̹����� �����ϱ����� �����̳ʸ� �����Ѵ�.
	multimap<int, CTexture*>		m_mapTex;

public:
	void AddTexture(PTCHAR pFileName, TEXTYPE Textype, int iObjID
		, int iStateID = 0, int iCnt = 0); // (���ϰ��, ��Ƽor�̱�, ��ü����, ��ü���±���, ����)
public:
//					��ü����				��ü����						���°��?
//GetTexture(OBJECT_BACKGROUND, OBJECT_STATEID_BACKGROUND_TILE, m_vecTile[iIndex]->iDrawID)
/*
#����

	m_mapTex<OBJECT_BACKGROUND,CMultiTexture>
	�θ� CTexture �ȿ��� �̷��� �Ǿ��ִ� 

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
			ERRORCHK(L"�ؽ��İ� �����ϴ�!");
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
