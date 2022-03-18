#include "framework.h"
#include "CEventManager.h"
#include "CScene.h"
#include "CGameObject.h"
#include "AI.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Execute(const tEvent& event)
{
	switch (event.eEvent)
	{
	case TYPE_EVENT::CREATE_OBJECT:
	{
		// create Object
		// lParam : object �ּ�
		// wParam : group
		CGameObject* pObj = (CGameObject*)event.lParam;
		GROUP_GAMEOBJ group = (GROUP_GAMEOBJ)event.wParam;

		CSceneManager::GetInst()->GetCurrentScene()->AddObject(pObj, group);
	}
		break;
	case TYPE_EVENT::DELETE_OBJECT:
	{
		// Delete Object
		// lParam : object �ּ�
		// ��Ȱ��ȭ ��(����) ������ ������Ʈ ����
		CGameObject* pObj = (CGameObject*)event.lParam;
		if (pObj->IsDisabled()) return;

		pObj->SetDisable();
		m_vecDisableObj.push_back(pObj);
	}
		break;
	case TYPE_EVENT::ChangeScene:
	{
		// Change Scene
		// lParam : Scene �׷� ������
		GROUP_SCENE scene = (GROUP_SCENE)event.lParam;
		CUIManager::GetInst()->SetFocusedUI(nullptr);

		CSceneManager::GetInst()->ChangeScene(scene);
	}
		break;

	case TYPE_EVENT::CHANGE_AI_STATE:
	{
		// Change Enemy AI State
		// lParam : AI ������ ����
		// wParam : ENEMY_STATE

		AI* pAI = (AI*)event.lParam;
		ENEMY_STATE eEnmState = (ENEMY_STATE)event.wParam;

		pAI->ChangeState(eEnmState);
	}
		break;
	}
}

void CEventManager::update()
{
	// ��ϵ� ���� ���� ������Ʈ�� ����
	for (int i = 0; i < m_vecDisableObj.size(); ++i)
	{
		delete m_vecDisableObj[i];
	}
	m_vecDisableObj.clear();

	// �̺�Ʈ ó��
	for (int i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::AddEvent(const tEvent& event)
{
	m_vecEvent.push_back(event);
}

void CEventManager::EventCreateObj(CGameObject* pObj, GROUP_GAMEOBJ group)
{
	tEvent event;
	event.eEvent = TYPE_EVENT::CREATE_OBJECT;
	event.lParam = (DWORD_PTR)pObj;
	event.wParam = (DWORD_PTR)group;

	AddEvent(event);
}

void CEventManager::EventDeleteObj(CGameObject* pObj)
{
	tEvent event;
	event.eEvent = TYPE_EVENT::DELETE_OBJECT;
	event.lParam = (DWORD_PTR)pObj;

	AddEvent(event);
}

void CEventManager::EventChangeScene(GROUP_SCENE scene)
{
	tEvent event;
	event.eEvent = TYPE_EVENT::ChangeScene;
	event.lParam = (DWORD_PTR)scene;

	AddEvent(event);
}

void CEventManager::EventChangeAIState(AI* pAI, ENEMY_STATE eNextState)
{
	tEvent event;
	event.eEvent = TYPE_EVENT::CHANGE_AI_STATE;
	event.lParam = (DWORD_PTR)pAI;
	event.wParam = (DWORD_PTR)eNextState;

	AddEvent(event);
}
