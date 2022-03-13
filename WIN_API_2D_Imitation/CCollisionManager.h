#pragma once

union COLLISION_ID
{
	struct
	{
		UINT leftID;
		UINT rightID;
	};
						// �� 32bit + �� 32bit == KEY(64bit)
	ULONGLONG colID;	// leftID + rightID == uColliderID
};

class CCollider;

// �浹ü �� �浹 ���� Ŭ����
class CCollisionManager
{
	SINGLETON(CCollisionManager);
private:
	// ���� �׷찣�� �浹�� ��Ʈ�� ���ؼ� ����
	// ex) m_arrCheckGroup[eGroup_GameObj::Player] = 0000 0000 0000 1100 �̶��
	// Player�׷��� 3��°, 2��° �׷�� �浹 �����ϵ��� üũ
	UINT m_arrCheckGroup[(UINT)GROUP_GAMEOBJ::SIZE];

	// �浹ü ���� ���� �浹 ����
	map<ULONGLONG, bool> m_mapCollisionInfo;

public:
	void init();
	void update();

	// �׷찣�� �浹 ���� ������Ʈ
	// �� �׷��� ���� ������Ʈ���� �浹 �ߴ��� ���ߴ���, ����� �浹 ������ �ƴ��� ������Ʈ ����
	void CollisionGroupUpdate(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);
	// �� �׷��� �浹 �ߴ��� ���ߴ��� �˻�
	bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);

	// �浹 �˻縦 �ؾ��� ������Ʈ üũ
	void CheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);

	// �浹 ���� üũ�� �Ǿ��ִ� �׷���� ����
	void UnCheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);

	// ��� �浹ü�� ���� �浹 üũ ����
	void Reset();
};

