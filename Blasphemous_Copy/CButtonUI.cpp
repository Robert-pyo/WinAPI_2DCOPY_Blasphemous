#include "framework.h"
#include "CButtonUI.h"
#include "CD2DImage.h"

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
			GetFinalPos().x - GetScale().x,
			GetFinalPos().y - GetScale().y + 2.f,
			GetFinalPos().x + GetScale().x * 2.f,
			(GetFinalPos().y + GetScale().y * 2.f) + 2.f,
			30, GetTxtShadowColor());

		CRenderManager::GetInst()->RenderText(GetText(),
			GetFinalPos().x - GetScale().x,
			GetFinalPos().y - GetScale().y,
			GetFinalPos().x + GetScale().x * 2.f,
			GetFinalPos().y + GetScale().y * 2.f,
			30, GetTextColor());
	}
	else
	{
		CUI::render();
	}

	if (nullptr != m_pImg)
	{
		CRenderManager::GetInst()->RenderImage(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y
		);
	}
}

void CButtonUI::MouseOn()
{
	if (CUIManager::GetInst()->IsKeyControlled() && GetText() != L"")
		SetTextColor(RGB(255, 255, 0));
}

void CButtonUI::MouseLBtnDown()
{
}

void CButtonUI::MouseLBtnUp()
{
	if (CUIManager::GetInst()->IsKeyControlled() && GetText() != L"")
		SetTextColor(RGB(255, 255, 255));
}

void CButtonUI::MouseLBtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CButtonUI::SetImage(CD2DImage* img)
{
	m_pImg = img;
}

CD2DImage* CButtonUI::GetImageInfo()
{
	return m_pImg;
}

void CButtonUI::SetText(const wstring& str)
{
	m_strText = str;
}

void CButtonUI::SetClickCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}
