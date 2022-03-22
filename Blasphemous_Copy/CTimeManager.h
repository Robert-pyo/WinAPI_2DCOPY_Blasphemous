#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	LARGE_INTEGER m_llCurCount;		// ���� ī��Ʈ (ll -> long long) : 32byte?!
	LARGE_INTEGER m_llPrevCount;	// ���� ī��Ʈ
	LARGE_INTEGER m_llFrequency;	// �ʴ� ī��Ʈ Ƚ��

	unsigned int m_iFPS;
	double		 m_dDeltaTime;		// ��Ÿ Ÿ��

public:
	void update();
	void init();

	unsigned int	GetFPS()		{ return m_iFPS; }
	double			GetDeltaTime()	{ return m_dDeltaTime; }
};

