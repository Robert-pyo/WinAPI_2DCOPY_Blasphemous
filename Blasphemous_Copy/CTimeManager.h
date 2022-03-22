#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	LARGE_INTEGER m_llCurCount;		// 현재 카운트 (ll -> long long) : 32byte?!
	LARGE_INTEGER m_llPrevCount;	// 이전 카운트
	LARGE_INTEGER m_llFrequency;	// 초당 카운트 횟수

	unsigned int m_iFPS;
	double		 m_dDeltaTime;		// 델타 타임

public:
	void update();
	void init();

	unsigned int	GetFPS()		{ return m_iFPS; }
	double			GetDeltaTime()	{ return m_dDeltaTime; }
};

