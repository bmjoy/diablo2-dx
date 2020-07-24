#pragma once

template <typename T>
class CSingleTon
{
private:
	static T* m_pInstance;
public:
	static inline T* GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new T;
		return m_pInstance;
	}
public:
	inline void DestroyInstance(void)
	{
		SAFE_DELETE(m_pInstance);		
	}
protected:
	CSingleTon(void) {}
public:
	~CSingleTon(void) {}
};


template <typename T> T* CSingleTon<T>::m_pInstance = NULL;
