#pragma once

// �ؽ��� ������ ������ �ִ� Ŭ�������� �θ�.
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
