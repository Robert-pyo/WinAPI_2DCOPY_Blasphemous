#include "framework.h"
#include "CButtonUI.h"

CButtonUI::CButtonUI()
{
	m_pFunc = nullptr;
	m_pParam1 = {};
	m_pParam2 = {};
	m_strText = L"";
	m_color = RGB(255.f, 255.f, 255.f);
	m_shadowColor = RGB(0.f, 0.f, 0.f);
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
	if (m_strText != L"")
	{
		CRenderManager::GetInst()->RenderText(m_strText,
			GetPos().x - GetScale().x,
			GetPos().y - GetScale().y + 2.f,
			GetPos().x + GetScale().x * 2.f,
			(GetPos().y + GetScale().y * 2.f) + 2.f,
			30.f, m_shadowColor);

		CRenderManager::GetInst()->RenderText(m_strText,
			GetPos().x - GetScale().x,
			GetPos().y - GetScale().y,
			GetPos().x + GetScale().x * 2.f,
			GetPos().y + GetScale().y * 2.f,
			30.f, m_color);
	}
	else
	{
		CUI::render();
	}
}

void CButtonUI::MouseOn()
{
	m_color = RGB(255.f, 255.f, 0.f);
}

void CButtonUI::MouseLBtnDown()
{
	m_color = RGB(255.f, 255.f, 0.f);
}

void CButtonUI::MouseLBtnUp()
{
	m_color = RGB(255.f, 255.f, 255.f);
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

void CButtonUI::LoadImg(const wstring& strKey, const wstring& strRelativePath)
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strRelativePath);
}

void CButtonUI::SetText(const wstring& text)
{
	m_strText = text;
}
