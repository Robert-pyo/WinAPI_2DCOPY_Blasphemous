#pragma once

class CCollider;
class CAnimator;

enum class GROUP_GAMEOBJ;

class CGameObject
{
	friend class CEventManager;

protected:
	wstring m_strName;

	fPoint m_fptPos;
	fPoint m_fptScale;

	bool m_bIsActive;	// ������Ʈ ���� ����
	void SetDisable();	// ��Ȱ��ȭ ���·� ����

	// Collider�� ������Ʈ�ν� �����Ѵ�.
	// �� ������Ʈ�� Collider�� ���� ����, ������ ���� ���� �ִ�.
	// ���� ������Ʈ�� �����Ͽ� ������� CGameObject�� �θ�Ŭ������ �δ���
	// collider�� ����ϴ� ��ü�� ������� �ʴ� ��ü�� ���� �� �ִ�.
	CCollider* m_pCollider;

	// �ִϸ����� ������Ʈ
	CAnimator* m_pAnimator;

	GROUP_GAMEOBJ objGroup;

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() = 0;

	virtual void update() = 0;

	// collider�� ��� ��ü�� ������Ʈ�� ���� �� ����� ����Ǿ�� �Ѵ�.
	// ���� Player��ü�� ������Ʈ�� �������� ���� �浹 ����� �̷�������� enemy��ü�� ������Ʈ�� ���� �ʾҴٸ�
	// ���� �浹���� �ʾҴµ��� �浹�Ǿ��ٰ� ���� �� �����Ƿ� �� ��� ������Ʈ�� ���� �� ����Ǿ���Ѵ�.
	// �׷��Ƿ� �浹�� ����� FinalUpdate()���� �����Ѵ�.
	virtual void finalUpdate();	// CGameObject�� ��ӹ��� Ŭ������ �������̵� �ϴ� ���� ���� ���� final Ű���� ����

	virtual void render(HDC hDC) = 0;

	virtual void component_render(HDC hDC);

	void initObject	(const fPoint m_fptPos, const fPoint m_fptScale);

	wstring GetName();
	fPoint	GetPos();
	fPoint	GetScale();
	bool	IsDisabled();
	// ��ü�� �����ϰ��ִ� Collider�� ��ȯ�Ѵ�.
	CCollider* GetCollider();
	CAnimator* GetAnimator();

	void	SetName(const wstring& name);
	void	SetPos(const fPoint& m_fptPos);
	void	SetScale(const fPoint& m_fptScale);

	void SetObjGroup(const GROUP_GAMEOBJ& type);
	GROUP_GAMEOBJ GetObjGroup();

	// �ٸ� ������ collider�� �����ϴ°� �ƴ� ������Ʈ �ڽſ��� �����ؾ� �ϹǷ�
	// SetCollider�� �ƴ϶� CreateCollider�� ���
	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* target) {}
	virtual void OnCollisionEnter(CCollider* target) {}
	virtual void OnCollisionExit(CCollider* target) {}
};