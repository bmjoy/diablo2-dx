#include "StdAfx.h"
#include "TimeMgr.h"

CTimeMgr::CTimeMgr(void)
: m_fTime(0.f)
{
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_InvaliTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);
}

CTimeMgr::~CTimeMgr(void)
{
}


void CTimeMgr::SetPixelPerSec(void)
{
	QueryPerformanceCounter(&m_InvaliTime);

	if(m_InvaliTime.QuadPart - m_FixTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_InvaliTime;
	}

	m_fTime = (m_InvaliTime.QuadPart - m_LastTime.QuadPart ) / float(m_CpuTick.QuadPart);

	m_LastTime = m_InvaliTime;

}