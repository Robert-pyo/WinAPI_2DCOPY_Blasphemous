#pragma once

class CCollider;
class CAnimator;

enum class GROUP_GAMEOBJ;

class CGameObject
{
	friend class CEventManager;

private:
	wstring m_strName;

	fPoint m_fptPos;
	fPoint m_fptScale;

	bool m_bIsActive;	// ������Ʈ ���� ����

	// Collider�� ������Ʈ�ν� �����Ѵ�.
	// �� ������Ʈ�� Collider�� ���� ����, ������ ���� ���� �ִ�.
	// ���� ������Ʈ�� �����Ͽ� ������� CGameObject�� �θ�Ŭ������ �δ���
	// collider�� ����ϴ� ��ü�� ������� �ʴ� ��ü�� ���� �� �ִ�.
	CCollider* m_pCollider;

	// �ִϸ����� ������Ʈ
	CAnimator* m_pAnimator;

	GROUP_GAMEOBJ objGroup;

protected:
	void SetDisable();	// ��Ȱ��ȭ ���·� ����

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
	virtual void finalUpdate();

	virtual void render() = 0;

	virtual void component_render();

	virtual void debug_render();

public:
	void InitObject	(const fPoint m_fptPos, const fPoint m_fptScale);

	wstring GetName();
	fPoint	GetPos();
	fPoint	GetScale();
	bool	IsDisabled();

	void	SetName(const wstring& name);
	void	SetPos(const fPoint& m_fptPos);
	void	SetScale(const fPoint& m_fptScale);

	void SetObjGroup(const GROUP_GAMEOBJ& type);
	GROUP_GAMEOBJ GetObjGroup();

public:
	// �ٸ� ������ collider�� �����ϴ°� �ƴ� ������Ʈ �ڽſ��� �����ؾ� �ϹǷ�
	// SetCollider�� �ƴ϶� CreateCollider�� ���
	void CreateCollider();
	void CreateAnimator();

	// ��ü�� �����ϰ��ִ� Collider�� ��ȯ�Ѵ�.
	CCollider* GetCollider();
	CAnimator* GetAnimator();

public:
	virtual void OnCollision(CCollider* target) {}
	virtual void OnCollisionEnter(CCollider* target) {}
	virtual void OnCollisionExit(CCollider* target) {}
};