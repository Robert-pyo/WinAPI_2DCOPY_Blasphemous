#pragma once
#include "CGameObject.h"
class CUI : public CGameObject
{
	friend class CUIManager;

private:
	// �ڽ� UI������Ʈ
	vector<CUI*> m_vecChildUI;

	// �θ� UI������Ʈ
	CUI* m_pParentUI;

	fPoint m_fptFinalPos;

	// ī�޶��� ������ �޴� UI�̸� true, �ƴϸ� false
	bool m_bCamAffected;
	// UI�� ���� �����ӿ� ���콺�� �÷��� �־��ٸ� true, �ƴϸ� false
	bool m_bMouseOn;
	// UI�� ���� �����ӿ� ���Ⱦ��ٸ� true, �ƴ϶�� false
	bool m_bLBtnDown;

public:
	CUI();
	CUI(const CUI& other);
	virtual ~CUI();

	virtual CUI* Clone();

	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC hDC);

	// ���������� ���� �ڽĵ��� update, finalUpdate, render
	void update_child();
	void finalUpdate_child();
	void render_child(HDC hDC);

	virtual void MouseOn();
	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseLBtnClicked();

	void SetCamAffected(bool isAffected);

	fPoint	GetFinalPos();
	CUI*	GetParent();
	const vector<CUI*>& GetChildUI();
	bool	GetCamAffected();

	bool	IsMouseOn();
	bool	IsLBtnDown();

	void AddChild(CUI* pUI);

private:
	void MouseOnCheck();
};

