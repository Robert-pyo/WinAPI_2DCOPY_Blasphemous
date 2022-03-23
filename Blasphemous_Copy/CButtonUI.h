#pragma once
#include "CUI.h"

class CD2DImage;

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

public:
	virtual void render();

	virtual void MouseOn() override;
	virtual void MouseLBtnDown() override;
	virtual void MouseLBtnUp() override;
	virtual void MouseLBtnClicked() override;

	void SetImage(CD2DImage* img);
	void SetText(const wstring& str);

	void SetClickCallBack(BTN_FUNC func, DWORD_PTR param1, DWORD_PTR param2);
};

