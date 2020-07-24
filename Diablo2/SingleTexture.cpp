#include "StdAfx.h"
#include "SingleTexture.h"

#include "Device.h"

CSingleTexture::CSingleTexture(void)
: m_pTex(NULL)
{
}

CSingleTexture::~CSingleTexture(void)
{
	Release();
}


void CSingleTexture::LoadTexture(PTCHAR pFileName, int iStateID, int iCnt)
{
	D3DXIMAGE_INFO			ImgInfo;
	ZeroMemory(&ImgInfo, sizeof(ImgInfo));

	D3DXGetImageInfoFromFile(pFileName, &ImgInfo);

	if(FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(), pFileName
		, ImgInfo.Width, ImgInfo.Height, ImgInfo.MipLevels, 0, ImgInfo.Format
		, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255, 255, 0, 255) 
		, &ImgInfo, NULL, &m_pTex)))
		
	{
		ERRORCHK(pFileName);
		return;
	}
}

void CSingleTexture::Release( void )
{
	m_pTex->Release();
}

