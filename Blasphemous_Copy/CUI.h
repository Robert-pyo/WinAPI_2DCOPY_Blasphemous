#pragma once
#include "CGameObject.h"
class CUI : public CGameObject
{
	friend class CUIManager;

private:
	// 자식 UI오브젝트
	vector<CUI*> m_vecChildUI;

	// 부모 UI오브젝트
	CUI* m_pParentUI;

	fPoint m_fptFinalPos;

	// 카메라의 영향을 받는 UI이면 true, 아니면 false
	bool m_bCamAffected;
	// UI가 이전 프레임에 마우스가 올려져 있었다면 true, 아니면 false
	bool m_bMouseOn;
	// UI가 이전 프레임에 눌렸었다면 true, 아니라면 false
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

	// 계층구조를 위한 자식들의 update, finalUpdate, render
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

