#include "StdAfx.h"
#include "Device.h"

CDevice::CDevice(void)
: m_p3D(NULL)
, m_pDevice(NULL)
, m_pLine(NULL)
, m_pSprite(NULL)
{
}

CDevice::~CDevice(void)
{
	Release();
}


HRESULT CDevice::Initialize(void)
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	// 장치의 정보를 담기위한 구조체.
	D3DCAPS9		d3dcaps;
	//memset(&d3dcaps, 0, sizeof(d3dcaps));
	ZeroMemory(&d3dcaps, sizeof(d3dcaps));

	// 장치의 정보를 얻어오자.
	if(FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps)))
	{
		ERRORCHK(L"장치정보가져오기실패");
		return E_FAIL;
	}

	// 장치 정보 조사 ( 버텍스 프로세싱 : 변환, 조명)
	DWORD	vp = 0;

	if(d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;		
	}

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// 장치를 대표하는 객체를 만들자.
	if(FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp
		, &d3dpp, &m_pDevice)))
	{
		ERRORCHK(L"장치생성실패");
		return E_FAIL;
	}

	D3DXCreateLine(m_pDevice, &m_pLine);

	D3DXCreateSprite(m_pDevice, &m_pSprite);

	D3DXFONT_DESC		d3dfont;
	ZeroMemory(&d3dfont, sizeof(d3dfont));

	d3dfont.Height = 15;
	d3dfont.Width = 10;
	d3dfont.Weight = 20;
	lstrcpy(d3dfont.FaceName, L"굴림");
	d3dfont.CharSet = HANGUL_CHARSET;

	D3DXCreateFontIndirect(m_pDevice, &d3dfont, &m_pFont);

	return S_OK;
}

void CDevice::Release(void)
{
	m_pLine->Release();
	m_pLine = NULL;

	m_pDevice->Release();
	m_pDevice = NULL;

	m_p3D->Release();
	m_p3D = NULL;
}