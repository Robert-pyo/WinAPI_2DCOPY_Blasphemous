#pragma once
class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI* m_pFocusedUI;

	bool m_bIsKeyControl;

public:
	void update();
	void SetFocusedUI(CUI* pUI);

	void SetKeyControl(bool bRemote) { m_bIsKeyControl = bRemote; }
	bool IsKeyControlled() { return m_bIsKeyControl; }

private:
	CUI* GetTargetUI(CUI* pParentUI);
	CUI* GetFocusedUI();
};

