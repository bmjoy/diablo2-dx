#pragma once
#include "singleton.h"
#include "Defines.h"
#include "Device.h"

class CSoundMgr
	: public CSingleTon<CSoundMgr>
{
private:
	//다이렉트 사운드 인터페이스
	LPDIRECTSOUND				m_pSound;
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;
public:
	HRESULT Init(void);
	HRESULT LoadWave(TCHAR* pFileName);	//파일경로를 통해 파일을 읽어 들이겠다.
	void SoundPlay(int iIndex, DWORD dwFlag); //파일을 재생 하겠다.
	void SoundStop(int iIndex);
	bool SoundPlaying(int iIndex);	

	friend CSoundMgr* CSingleTon<CSoundMgr>::GetInstance();
private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};
