#pragma once

class CGameObject;

struct tEvent
{
	TYPE_EVENT	eEvent;		// 이벤트 타입
	DWORD_PTR	lParam;		// 추가적인 정보1
	DWORD_PTR	wParam;		// 추가적인 정보2
};

/// <summary>
/// 게임 진행 중, 업데이트 중에 오브젝트가 사라지거나 갑자기 생기게 될 경우,
/// 버그가 생길 확률이 매우 높으므로 업데이트 시작 전에 개체 생성 및 삭제, 씬 전환 등
/// 이벤트들을 먼저 처리한 후 다른 업데이트를 수행하기 위한 이벤트 매니저.
/// </summary>
class CEventManager
{
	SINGLETON(CEventManager);
	
private:
	vector<tEvent> m_vecEvent;
	vector<CGameObject*> m_vecDisableObj;

	// 이벤트 처리
	void Execute(const tEvent& event);
public:
	void update();

	// 이벤트 매니저의 대기열에 이벤트 추가
	void AddEvent(const tEvent& event);
	// 오브젝트 생성 이벤트
	void EventCreateObj(CGameObject* pObj, GROUP_GAMEOBJ group);
	// 오브젝트 삭제 이벤트
	void EventDeleteObj(CGameObject* pObj);
	// 씬 체인지 이벤트
	void EventChangeScene(GROUP_SCENE scene);
};

