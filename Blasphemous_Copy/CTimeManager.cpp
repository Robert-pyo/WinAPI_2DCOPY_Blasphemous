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

	QueryPerformanceCounter(&m_llCurCount); // ���� ī��Ʈ ����

	// ������Ʈ �Ǵµ� �󸶳� ī��Ʈ�� �������� / 1�ʿ� ī��Ʈ ����Ǵ���
	// -> ������Ʈ�� ������Ʈ ���̿� �󸶳� �ð��� �ɷȴ��� �� �� ����
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;

	// ��� �����ؾ� �ϹǷ� ���� ī��Ʈ ������ ���� ī��Ʈ ������ �־���
	m_llPrevCount = m_llCurCount;

	++updateCount;
	updateOneSecond += m_dDeltaTime;
	if (updateOneSecond >= 1.0) // 1�ʰ� ���� �ƴٸ�
	{
		m_iFPS = updateCount;  // �ʴ� ������Ʈ Ƚ�� == FPS
		updateCount = 0;
		updateOneSecond = 0;
	}
}

void CTimeManager::init()
{
	QueryPerformanceCounter(&m_llPrevCount);		// ���� �ð��� ī��Ʈ ��(�ʱ�ȭ ��)
	QueryPerformanceFrequency(&m_llFrequency);		// 1�ʴ� �����ϴ� ī��Ʈ ��
}
