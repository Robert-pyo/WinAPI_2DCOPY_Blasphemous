#include "framework.h"
#include "CKeyManager.h"



CKeyManager::CKeyManager()
{
	// Ű ���¸� ��� ������ ���� ���·� �ʱ�ȭ
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

	// ���� ������ ���� �� ������ true ��� false�� �ٲ���
	if (m_bIsAnyKeyCurPressed)
		m_bIsAnyKeyCurPressed = false;

	// ���� ���� �����찡 ���õ� �����찡 �ƴ� ���
	if (hWnd != GetFocus())
	{
		// Ű�Է��� ��� ����(false)
		for (int key = 0; key < VK_SIZE; ++key)
		{
			m_arrPrevKey[key]	= m_arrCurKey[key];
			m_arrCurKey[key]	= false;
		}
		// ��� ���� ��Ų �� Ű �Է� ���� ���ϵ��� ��ȯ
		return;
	}

	// ��� Ű ������ ��ŭ �ݺ��ϸ鼭 �� Ű�� �Է� ���¸� Ȯ��
	for (int key = 0; key < VK_SIZE; ++key)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];

		// ��Ʈ ����ŷ�� ���� Ű�� ���ȴ��� �ȴ��ȴ����� �ش��ϴ� ��Ʈ�� AND����
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

	// ���콺 ��ǥ�� ��� ������ POINT ����
	POINT ptPos = {};
	// �����쿡�� ����� �»�� ���� ���콺�� ��ǥ�� ��ȯ
	GetCursorPos(&ptPos);
	// ���� ������ ���� ���콺��ġ�� ���
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
