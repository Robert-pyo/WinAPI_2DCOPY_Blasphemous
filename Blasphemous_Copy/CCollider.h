#pragma once

class CGameObject;

// �浹ü ������Ʈ
class CCollider
{
	friend CGameObject;
private:
	// Collider ���� ID -> ��� collider ����
	static UINT s_iUID;

	// Collider ���� ������Ʈ
	CGameObject* m_pOwner;

	// Collider�� ��ġ
	fPoint m_fptFinalPos;

	// Collider�� ������Ʈ�� �߽����κ���
	// ����������� �󸶳� �������ִ��� �����ϱ� ���� Offset
	fPoint m_fptOffsetPos;

	// Collider�� LeftTopRightBottom�� �����ϱ����� ����
	RECT m_rtCollider;

	// Collider�� ũ��
	fPoint m_fptScale;

	// Collider ���� ���̵� -> ���� ID�� �������� collider �߰� �ɶ����� 1�� ����
	UINT m_iUID;

	// �浹 ī��Ʈ
	UINT m_iCollisionCount;

public:
	CCollider	();
	~CCollider	();
	CCollider(const CCollider& other);

	fPoint	GetFinalPos		();
	fPoint	GetOffsetPos	();
	fPoint	GetScale		();
	RECT	GetBorderPos	();
	
	// �浹ü ���� ID ��ȯ
	UINT GetID();

	void SetFinalPos	(fPoint m_fptPos);
	void SetOffsetPos	(fPoint offset);
	void SetScale		(fPoint m_fptScale);

	void finalUpdate();
	void render();

	CGameObject* GetOwnerObj();

	// �浹ü ������ �浹�� ���� ó���� ���� �ٸ��� ó���� �� �ֵ��� �� ��

	void OnCollision(CCollider* target);
	void OnCollisionEnter(CCollider* target);
	void OnCollisionExit(CCollider* target);
};

