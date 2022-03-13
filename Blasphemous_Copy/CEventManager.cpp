#include "framework.h"
#include "CEventManager.h"
#include "CScene.h"
#include "CGameObject.h"

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
		// lParam : object 주소
		// wParam : group
		CGameObject* pObj = (CGameObject*)event.lParam;
		GROUP_GAMEOBJ group = (GROUP_GAMEOBJ)event.wParam;

		CSceneManager::getInst()->GetCurrentScene()->AddObject(pObj, group);
	}
		break;
	case TYPE_EVENT::DELETE_OBJECT:
	{
		// Delete Object
		// lParam : object 주소
		// 비활성화 될(죽을) 예정인 오브젝트 관리
		CGameObject* pObj = (CGameObject*)event.lParam;
		pObj->SetDisable();
		m_vecDisableObj.push_back(pObj);
	}
		break;
	case TYPE_EVENT::CHANGE_SCENE:
		// Change Scene
		// lParam : Scene 그룹 열거형
		GROUP_SCENE scene = (GROUP_SCENE)event.lParam;
		CUIManager::getInst()->SetFocusedUI(nullptr);

		CSceneManager::getInst()->ChangeScene(scene);

		break;
	}
}

void CEventManager::update()
{
	// 등록된 삭제 예정 오브젝트들 삭제
	for (int i = 0; i < m_vecDisableObj.size(); ++i)
	{
		delete m_vecDisableObj[i];
	}
	m_vecDisableObj.clear();

	// 이벤트 처리
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
	event.eEvent = TYPE_EVENT::CHANGE_SCENE;
	event.lParam = (DWORD_PTR)scene;

	AddEvent(event);
}
