#pragma once

class CGameObject;

struct tEvent
{
	TYPE_EVENT	eEvent;		// �̺�Ʈ Ÿ��
	DWORD_PTR	lParam;		// �߰����� ����1
	DWORD_PTR	wParam;		// �߰����� ����2
};

/// <summary>
/// ���� ���� ��, ������Ʈ �߿� ������Ʈ�� ������ų� ���ڱ� ����� �� ���,
/// ���װ� ���� Ȯ���� �ſ� �����Ƿ� ������Ʈ ���� ���� ��ü ���� �� ����, �� ��ȯ ��
/// �̺�Ʈ���� ���� ó���� �� �ٸ� ������Ʈ�� �����ϱ� ���� �̺�Ʈ �Ŵ���.
/// </summary>
class CEventManager
{
	SINGLETON(CEventManager);
	
private:
	vector<tEvent> m_vecEvent;
	vector<CGameObject*> m_vecDisableObj;

	// �̺�Ʈ ó��
	void Execute(const tEvent& event);
public:
	void update();

	// �̺�Ʈ �Ŵ����� ��⿭�� �̺�Ʈ �߰�
	void AddEvent(const tEvent& event);
	// ������Ʈ ���� �̺�Ʈ
	void EventCreateObj(CGameObject* pObj, GROUP_GAMEOBJ group);
	// ������Ʈ ���� �̺�Ʈ
	void EventDeleteObj(CGameObject* pObj);
	// �� ü���� �̺�Ʈ
	void EventChangeScene(GROUP_SCENE scene);
};

