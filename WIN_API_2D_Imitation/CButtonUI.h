#pragma once
#include "CUI.h"

// 함수 포인터를 위한 타입 정의
typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class CButtonUI : public CUI
{
private:
	BTN_FUNC	m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

public:
	CButtonUI();
	~CButtonUI();

	virtual CButtonUI* Clone();

	virtual void MouseOn() override;
	virtual void MouseLBtnDown() override;
	virtual void MouseLBtnUp() override;
	virtual void MouseLBtnClicked() override;

	void SetClickCallBack(BTN_FUNC func, DWORD_PTR param1, DWORD_PTR param2);
};

