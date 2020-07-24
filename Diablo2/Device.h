#pragma once

#include "Defines.h"
#include "SingleTon.h"

// ��ġ �ʱ�ȭ�� ��Ȱ�� �����Ѵ�.
// 1. �� ��ǻ�Ϳ� �ִ� ��ġ�� ������ �����Ѵ�.
// 2. �� ��ǻ�Ϳ� �ִ� ��ġ�� ��ǥ�ϴ� ��ü�� �����Ѵ�.
class CDevice
	: public CSingleTon<CDevice>
{
private:
	// 1��° ����� �����ϱ� ���� ��ü.
	LPDIRECT3D9				m_p3D;

	// ��ġ�� ��ǥ�ϴ� ��ü
	LPDIRECT3DDEVICE9		m_pDevice;

	// ������ �׸������� ��ä
	LPD3DXLINE				m_pLine;

	// �̹������õ� ���� �ϱ� ���� ��ü.
	LPD3DXSPRITE			m_pSprite;

	// �۾��� �����.
	LPD3DXFONT				m_pFont;

public:
	// getter
	LPD3DXFONT	GetFont(void) const {return m_pFont;}
	LPD3DXSPRITE GetSprite(void) const {return m_pSprite;}
	LPDIRECT3DDEVICE9 GetDevice(void) const {return m_pDevice;}
	LPD3DXLINE GetLine(void) const {return m_pLine;}

public:
	HRESULT Initialize(void); // ��ġ�ʱ�ȭ�� ����� �����ϱ� ���� �Լ�.
	void Release(void);

	friend CDevice* CSingleTon<CDevice>::GetInstance();
private:
	CDevice(void);
public:
	~CDevice(void);
};
