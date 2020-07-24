#pragma once

// 텍스쳐 정보를 가지고 있는 클래스들의 부모.
class CTexture
{
public:
	virtual void LoadTexture(PTCHAR pFileName, int iStateID = 0, int iCnt = 0)PURE;
	virtual LPDIRECT3DTEXTURE9 GetTexture(int iStateID = 0, int iCnt = 0)PURE;
	virtual void Release(void)PURE;
public:
	CTexture(void);
	virtual ~CTexture(void);
};
