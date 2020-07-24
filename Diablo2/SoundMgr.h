#pragma once
#include "singleton.h"
#include "Defines.h"
#include "Device.h"

class CSoundMgr
	: public CSingleTon<CSoundMgr>
{
private:
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound;
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;
public:
	HRESULT Init(void);
	HRESULT LoadWave(TCHAR* pFileName);	//���ϰ�θ� ���� ������ �о� ���̰ڴ�.
	void SoundPlay(int iIndex, DWORD dwFlag); //������ ��� �ϰڴ�.
	void SoundStop(int iIndex);
	bool SoundPlaying(int iIndex);	

	friend CSoundMgr* CSingleTon<CSoundMgr>::GetInstance();
private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};
