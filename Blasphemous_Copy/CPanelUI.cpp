#include "framework.h"
#include "CPanelUI.h"

CPanelUI::CPanelUI()
{
	m_fptDragStart = {};
}

CPanelUI::~CPanelUI()
{
}

CPanelUI* CPanelUI::Clone()
{
	return new CPanelUI(*this);
}

void CPanelUI::MouseOn()
{
	if (IsLBtnDown())
	{
		fPoint fptDiff = MousePos() - m_fptDragStart;

		fPoint fptCurPos = GetPos();
		fptCurPos += fptDiff;
		SetPos(fptCurPos);

		m_fptDragStart = MousePos();
	}
}

void CPanelUI::MouseLBtnDown()
{
	m_fptDragStart = MousePos();
}

void CPanelUI::MouseLBtnUp()
{
}
