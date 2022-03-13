#include "framework.h"
#include "CButtonUI.h"

CButtonUI::CButtonUI()
{
	m_pFunc = nullptr;
	m_pParam1 = {};
	m_pParam2 = {};
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::Clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::MouseOn()
{
	// 마우스가 올라갔을 때 버튼이 하이라이트 표시
}

void CButtonUI::MouseLBtnDown()
{
	// 눌린 버튼 모양
}

void CButtonUI::MouseLBtnUp()
{
	// 다시 원본 모양
}

void CButtonUI::MouseLBtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CButtonUI::SetClickCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}
