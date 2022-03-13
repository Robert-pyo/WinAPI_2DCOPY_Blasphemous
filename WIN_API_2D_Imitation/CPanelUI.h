#pragma once
#include "CUI.h"
class CPanelUI : public CUI
{
private:
	fPoint m_fptDragStart;

public:
	CPanelUI();
	~CPanelUI();

	virtual CPanelUI* Clone();

	virtual void MouseOn() override;
	virtual void MouseLBtnDown() override;
	virtual void MouseLBtnUp() override;
};

