#include "framework.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{
	m_pFocusedUI = nullptr;
	m_bIsKeyControl = true;
}

CUIManager::~CUIManager()
{
}

void CUIManager::update()
{
	m_pFocusedUI = GetFocusedUI();
	CUI* pTargetUI = GetTargetUI(m_pFocusedUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (PRESS_KEY_DOWN(VK_LBUTTON))
		{
			pTargetUI->MouseLBtnDown();
			pTargetUI->m_bLBtnDown = true;
		}
		else if (PRESS_KEY_UP(VK_LBUTTON))
		{
			pTargetUI->MouseLBtnUp();

			if (pTargetUI->m_bLBtnDown)
			{
				pTargetUI->MouseLBtnClicked();
			}

			pTargetUI->m_bLBtnDown = false;
		}
	}
}

void CUIManager::SetFocusedUI(CUI* pUI)
{
	// 이미 pUI가 포커싱된 UI일 경우
	if (m_pFocusedUI == pUI || m_pFocusedUI == nullptr)
	{
		m_pFocusedUI = pUI;
		return;
	}

	m_pFocusedUI = pUI;

	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	vector<CGameObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CGameObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	if (vecUI.end() == iter)
		return;

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIManager::GetTargetUI(CUI* pParentUI)
{
	// 깊이 우선 탐색하며 최상단에 있는 자식UI를 target으로 가져오자

	list<CUI*> pUIList;
	vector<CUI*> vecNoneTarget;
	CUI* pTargetUI = nullptr;

	if (nullptr == pParentUI)
		return nullptr;

	pUIList.push_back(pParentUI);

	while (!pUIList.empty())
	{
		CUI* pUI = pUIList.front();
		pUIList.pop_front();

		if (pUI->IsMouseOn())
		{
			// 부모가 있었던 경우 -> 부모에서 자식으로 따라들어가기 때문
			// 자식이 targetUI가 되었다면 부모는 NoneTarget
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			// 애초에 MouseOn이 아닌 UI들은 NoneTarget
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*> vecChild = pUI->GetChildUI();
		for (UINT i = 0; i < vecChild.size(); ++i)
		{
			pUIList.push_back(vecChild[i]);
		}
	}

	if (PRESS_KEY_UP(VK_LBUTTON))
	{
		for (UINT i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLBtnDown = false;
		}
	}

	return pTargetUI;
}

CUI* CUIManager::GetFocusedUI()
{
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	vector<CGameObject*>& vecUI = pCurScene->GetUIGroup();

	CUI* pFocusedUI = m_pFocusedUI;

	if (!PRESS_KEY_DOWN(VK_LBUTTON))
	{
		return pFocusedUI;
	}

	vector<CGameObject*>::iterator targetIter = vecUI.end();
	for (vector<CGameObject*>::iterator iter = vecUI.begin(); iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
			targetIter = iter;
	}

	// 포커싱된 UI가 없는 경우
	if (targetIter == vecUI.end())
		return nullptr;
	
	pFocusedUI = (CUI*)*targetIter;

	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);
	m_pFocusedUI = pFocusedUI;

	return pFocusedUI;
}
