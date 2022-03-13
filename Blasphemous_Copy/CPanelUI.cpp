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
		fPoint fptDiff = MOUSE_POS() - m_fptDragStart;

		fPoint fptCurPos = GetPos();
		fptCurPos += fptDiff;
		SetPos(fptCurPos);

		m_fptDragStart = MOUSE_POS();
	}
}

void CPanelUI::MouseLBtnDown()
{
	m_fptDragStart = MOUSE_POS();
}

void CPanelUI::MouseLBtnUp()
{
}
