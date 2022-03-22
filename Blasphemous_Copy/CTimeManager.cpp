#include "framework.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager()
{
	m_llCurCount = {};
	m_llPrevCount = {};
	m_llFrequency = {};
	m_iFPS = 0;
	m_dDeltaTime = 0;
}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::update()
{
	static unsigned int updateCount = 0;
	static double updateOneSecond = 0;

	QueryPerformanceCounter(&m_llCurCount); // 현재 카운트 개수

	// 업데이트 되는데 얼마나 카운트가 지났는지 / 1초에 카운트 몇번되는지
	// -> 업데이트와 업데이트 사이에 얼마나 시간이 걸렸는지 알 수 있음
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;

	// 계속 갱신해야 하므로 이전 카운트 갯수에 현재 카운트 갯수를 넣어줌
	m_llPrevCount = m_llCurCount;

	++updateCount;
	updateOneSecond += m_dDeltaTime;
	if (updateOneSecond >= 1.0) // 1초가 진행 됐다면
	{
		m_iFPS = updateCount;  // 초당 업데이트 횟수 == FPS
		updateCount = 0;
		updateOneSecond = 0;
	}
}

void CTimeManager::init()
{
	QueryPerformanceCounter(&m_llPrevCount);		// 현재 시간의 카운트 수(초기화 시)
	QueryPerformanceFrequency(&m_llFrequency);		// 1초당 진행하는 카운트 수
}
