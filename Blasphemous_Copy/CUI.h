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

	CD2DImage*	m_pImg;

	wstring		m_strText;
	COLORREF	m_rgbTxtColor;
	COLORREF	m_rgbTxtShadowColor;

public:
	CUI();
	CUI(const CUI& other);
	virtual ~CUI();

	virtual CUI* Clone();

public:
	virtual void update();
	virtual void finalUpdate();
	virtual void render();

	// ���������� ���� �ڽĵ��� update, finalUpdate, render
	void update_child();
	void finalUpdate_child();
	void render_child();

public:
	virtual void MouseOn();
	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseLBtnClicked();

	bool	IsMouseOn();
	bool	IsLBtnDown();

public:
	void SetCamAffected(bool isAffected);
	bool GetCamAffected();

	fPoint	GetFinalPos();

	CUI*	GetParent();
	const	vector<CUI*>& GetChildUI();
	void	AddChild(CUI* pUI);

public:
	void LoadImg(const wstring& strKey, const wstring& strRelativePath);

	void SetText(const wstring& text);
	const wstring& GetText();

	void SetTextColor(const COLORREF color);
	const COLORREF GetTextColor();

	void SetTxtShadowColor(const COLORREF color);
	const COLORREF GetTxtShadowColor();

public:
	void SelectUI();
	void DeselectUI();

private:
	void MouseOnCheck();
};

