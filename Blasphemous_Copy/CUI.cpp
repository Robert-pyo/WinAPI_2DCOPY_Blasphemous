#include "framework.h"
#include "CUI.h"

CUI::CUI()
{
	m_pParentUI = nullptr;
	m_bCamAffected = false;
	m_bMouseOn = false;
	m_bLBtnDown = false;
}

CUI::CUI(const CUI& other)
	: CGameObject(other)
{
	m_pParentUI = nullptr;
	m_bCamAffected = other.m_bCamAffected;
	m_bMouseOn = false;
	m_bLBtnDown = false;

	for (UINT i = 0; i < other.m_vecChildUI.size(); ++i)
	{
		AddChild(other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (UINT i = 0; i < m_vecChildUI.size(); ++i)
	{
		if (nullptr != m_vecChildUI[i])
			delete m_vecChildUI[i];
	}
}

CUI* CUI::Clone()
{
	return new CUI(*this);
}

void CUI::update()
{
	update_child();
}

void CUI::finalUpdate()
{
	// 원 기능 실행 먼저
	CGameObject::finalUpdate();

	m_fptFinalPos = GetPos();
	if (GetParent())
	{
		fPoint fptParentPos = GetParent()->GetFinalPos();
		m_fptFinalPos += fptParentPos;
	}

	MouseOnCheck();

	finalUpdate_child();
}

void CUI::render()
{
	fPoint fptFinalPos = GetFinalPos();
	fPoint fptPos	= GetPos();
	fPoint fptScale = GetScale();

	// 카메라 영향을 받는다면 렌더링 좌표를 카메라 기준으로
	if (m_bCamAffected)
	{
		fptFinalPos = CCameraManager::GetInst()->GetRenderPos(fptFinalPos);
	}

	if (m_bLBtnDown)
	{
		CRenderManager::GetInst()->RenderRectangle(
			fptPos.x,
			fptPos.y,
			fptPos.x + fptScale.x,
			fptPos.y + fptScale.y,
			RGB(0, 255, 0));
	}
	else
	{
		CRenderManager::GetInst()->RenderRectangle(
			fptPos.x,
			fptPos.y,
			fptPos.x + fptScale.x,
			fptPos.y + fptScale.y,
			RGB(0, 0, 0));
	}

	render_child();
}

void CUI::update_child()
{
	for (UINT i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalUpdate_child()
{
	for (UINT i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalUpdate();
	}
}

void CUI::render_child()
{
	for (UINT i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render();
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLBtnDown()
{
}

void CUI::MouseLBtnUp()
{
}

void CUI::MouseLBtnClicked()
{
}

void CUI::SetCamAffected(bool isAffected)
{
	m_bCamAffected = isAffected;
}

fPoint CUI::GetFinalPos()
{
	return m_fptFinalPos;
}

CUI* CUI::GetParent()
{
	return m_pParentUI;
}

const vector<CUI*>& CUI::GetChildUI()
{
	return m_vecChildUI;
}

bool CUI::GetCamAffected()
{
	return m_bCamAffected;
}

bool CUI::IsMouseOn()
{
	return m_bMouseOn;
}

bool CUI::IsLBtnDown()
{
	return m_bLBtnDown;
}

void CUI::AddChild(CUI* pUI)
{
	m_vecChildUI.push_back(pUI);
	pUI->m_pParentUI = this;
	pUI->SetCamAffected(this->m_bCamAffected);
}

void CUI::MouseOnCheck()
{
	fPoint fptMousePos = MousePos();
	fPoint fptScale = GetScale();

	if (m_bCamAffected)
	{
		fptMousePos = CCameraManager::GetInst()->GetRealPos(fptMousePos);
	}

	if (m_fptFinalPos.x <= fptMousePos.x && fptMousePos.x <= m_fptFinalPos.x + fptScale.x && 
		m_fptFinalPos.y <= fptMousePos.y && fptMousePos.y <= m_fptFinalPos.y + fptScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
