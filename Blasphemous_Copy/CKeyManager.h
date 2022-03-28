#pragma once
class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	static const int VK_SIZE = 0xff;

	bool m_arrPrevKey[VK_SIZE];		// 이전 키의 입력상태를 저장할 배열
	bool m_arrCurKey[VK_SIZE];		// 현재 키의 입력상태를 저장할 배열

	fPoint m_fptCurMousePos;			// 현재 마우스 좌표

	bool m_bIsAnyKeyCurPressed;
	bool m_bIsAnyKeyPrePressed;

public:
	void update();
	void init();

	bool GetButton(const int key);		// 키가 눌려진 상태면 true
	bool GetButtonDown(const int key);	// 키가 눌려진 순간 true
	bool GetButtonUp(const int key);	// 키가 눌렸다 떼진 순간 true
	bool GetAnyKeyDown();

	fPoint GetMousePos();				// 마우스 좌표 받기
};

