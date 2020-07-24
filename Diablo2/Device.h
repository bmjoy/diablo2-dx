#pragma once

#include "Defines.h"
#include "SingleTon.h"

// 장치 초기화의 역활을 수행한다.
// 1. 내 컴퓨터에 있는 장치의 성능을 조사한다.
// 2. 내 컴퓨터에 있는 장치를 대표하는 객체를 생성한다.
class CDevice
	: public CSingleTon<CDevice>
{
private:
	// 1번째 기능을 수행하기 위한 객체.
	LPDIRECT3D9				m_p3D;

	// 장치를 대표하는 객체
	LPDIRECT3DDEVICE9		m_pDevice;

	// 라인을 그리기위한 객채
	LPD3DXLINE				m_pLine;

	// 이미지관련된 일을 하기 위한 객체.
	LPD3DXSPRITE			m_pSprite;

	// 글씨를 띄우자.
	LPD3DXFONT				m_pFont;

public:
	// getter
	LPD3DXFONT	GetFont(void) const {return m_pFont;}
	LPD3DXSPRITE GetSprite(void) const {return m_pSprite;}
	LPDIRECT3DDEVICE9 GetDevice(void) const {return m_pDevice;}
	LPD3DXLINE GetLine(void) const {return m_pLine;}

public:
	HRESULT Initialize(void); // 장치초기화의 기능을 수행하기 위한 함수.
	void Release(void);

	friend CDevice* CSingleTon<CDevice>::GetInstance();
private:
	CDevice(void);
public:
	~CDevice(void);
};
