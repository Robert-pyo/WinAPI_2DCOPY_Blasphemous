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

void CButtonUI::render()
{
	if (GetText() != L"")
	{
		CRenderManager::GetInst()->RenderText(GetText(),
			GetPos().x - GetScale().x,
			GetPos().y - GetScale().y + 2.f,
			GetPos().x + GetScale().x * 2.f,
			(GetPos().y + GetScale().y * 2.f) + 2.f,
			30.f, GetTxtShadowColor());

		CRenderManager::GetInst()->RenderText(GetText(),
			GetPos().x - GetScale().x,
			GetPos().y - GetScale().y,
			GetPos().x + GetScale().x * 2.f,
			GetPos().y + GetScale().y * 2.f,
			30.f, GetTextColor());
	}
	else
	{
		CUI::render();
	}
}

void CButtonUI::MouseOn()
{
	if (GetText() != L"")
		SetTextColor(RGB(255.f, 255.f, 0.f));
}

void CButtonUI::MouseLBtnDown()
{
}

void CButtonUI::MouseLBtnUp()
{
	if (GetText() != L"")
		SetTextColor(RGB(255.f, 255.f, 255.f));
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
