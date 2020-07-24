#include "StdAfx.h"
#include "MultiTexture.h"

#include "Device.h"

CMultiTexture::CMultiTexture(void)
{
}

CMultiTexture::~CMultiTexture(void)
{
	Release();
}

void CMultiTexture::LoadTexture( PTCHAR pFileName, int iStateID, int iCnt )
{
	TCHAR		szPath[128];

	vector<LPDIRECT3DTEXTURE9>		vecTex;
	LPDIRECT3DTEXTURE9				pTex;

	for (int i = 0; i < iCnt; ++i)
	{
		wsprintf(szPath, pFileName, i);

		D3DXIMAGE_INFO			ImgInfo;
		ZeroMemory(&ImgInfo, sizeof(ImgInfo));

		D3DXGetImageInfoFromFile(szPath, &ImgInfo);

		if(FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(), szPath
			, ImgInfo.Width, ImgInfo.Height, ImgInfo.MipLevels, 0, ImgInfo.Format
			, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255, 255, 0, 255) 
			, &ImgInfo, NULL, &pTex)))

		{
			ERRORCHK(szPath);
			return;
		}
		vecTex.push_back(pTex);
	}
	m_MapTex.insert(make_pair(iStateID, vecTex));	
}

void CMultiTexture::Release( void )
{
	for (multimap<int, vector<LPDIRECT3DTEXTURE9>>::iterator	iter = m_MapTex.begin();
		iter != m_MapTex.end(); ++iter)
	{
		for (unsigned int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			iter->second[i] = NULL;
		}
		iter->second.clear();
	}
	m_MapTex.clear();

}
