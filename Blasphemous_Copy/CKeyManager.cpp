#include "framework.h"
#include "CKeyManager.h"



CKeyManager::CKeyManager()
{
	// 키 상태를 모두 눌리지 않은 상태로 초기화
	for (int key = 0; key < VK_SIZE; ++key)
	{
		m_arrCurKey[key] = false;
		m_arrPrevKey[key] = false;
	}
	m_bIsAnyKeyCurPressed = false;
	m_bIsAnyKeyPrePressed = false;
}

CKeyManager::~CKeyManager()
{
}

void CKeyManager::update()
{
	m_bIsAnyKeyPrePressed = m_bIsAnyKeyCurPressed;

	// 다음 프레임 시작 시 아직도 true 라면 false로 바꿔줌
	if (m_bIsAnyKeyCurPressed)
		m_bIsAnyKeyCurPressed = false;

	// 만약 게임 윈도우가 선택된 윈도우가 아닐 경우
	if (hWnd != GetFocus())
	{
		// 키입력을 모두 해제(false)
		for (int key = 0; key < VK_SIZE; ++key)
		{
			m_arrPrevKey[key]	= m_arrCurKey[key];
			m_arrCurKey[key]	= false;
		}
		// 모두 해제 시킨 후 키 입력 받지 못하도록 반환
		return;
	}

	// 모든 키 사이즈 만큼 반복하면서 그 키의 입력 상태를 확인
	for (int key = 0; key < VK_SIZE; ++key)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];

		// 비트 마스킹을 통해 키가 눌렸는지 안눌렸는지에 해당하는 비트에 AND연산
		// 1011 0011 1001 1111 & 1000 0000 0000 0000
		if (GetAsyncKeyState(key) & 0x8000)
		{
			m_arrCurKey[key] = true;
			m_bIsAnyKeyCurPressed = true;
		}
		else
		{
			m_arrCurKey[key] = false;
		}
	}

	// 마우스 좌표를 잠시 보관할 POINT 변수
	POINT ptPos = {};
	// 윈도우에서 모니터 좌상단 기준 마우스의 좌표를 반환
	GetCursorPos(&ptPos);
	// 게임 윈도우 기준 마우스위치로 계산
	ScreenToClient(hWnd, &ptPos);
	m_fptCurMousePos = fPoint((float)ptPos.x, (float)ptPos.y);
}

void CKeyManager::init()
{

}

bool CKeyManager::GetButton(const int key)
{
	return (true == m_arrPrevKey[key] && true == m_arrCurKey[key]);
}

bool CKeyManager::GetButtonDown(const int key)
{
	return (false == m_arrPrevKey[key] && true == m_arrCurKey[key]);
}

bool CKeyManager::GetButtonUp(const int key)
{
	return (true == m_arrPrevKey[key] && false == m_arrCurKey[key]);
}

bool CKeyManager::GetAnyKeyDown()
{
	if (!m_bIsAnyKeyPrePressed && m_bIsAnyKeyCurPressed)
	{
		m_bIsAnyKeyCurPressed = false;

		return true;
	}
	
	return false;
}

fPoint CKeyManager::GetMousePos()
{
	return m_fptCurMousePos;
}
