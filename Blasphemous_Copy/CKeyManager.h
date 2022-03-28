#pragma once
class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	static const int VK_SIZE = 0xff;

	bool m_arrPrevKey[VK_SIZE];		// ���� Ű�� �Է»��¸� ������ �迭
	bool m_arrCurKey[VK_SIZE];		// ���� Ű�� �Է»��¸� ������ �迭

	fPoint m_fptCurMousePos;			// ���� ���콺 ��ǥ

	bool m_bIsAnyKeyCurPressed;
	bool m_bIsAnyKeyPrePressed;

public:
	void update();
	void init();

	bool GetButton(const int key);		// Ű�� ������ ���¸� true
	bool GetButtonDown(const int key);	// Ű�� ������ ���� true
	bool GetButtonUp(const int key);	// Ű�� ���ȴ� ���� ���� true
	bool GetAnyKeyDown();

	fPoint GetMousePos();				// ���콺 ��ǥ �ޱ�
};

