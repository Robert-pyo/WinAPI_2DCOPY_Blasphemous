#pragma once

union COLLISION_ID
{
	struct
	{
		UINT leftID;
		UINT rightID;
	};
						// 앞 32bit + 뒤 32bit == KEY(64bit)
	ULONGLONG colID;	// leftID + rightID == uColliderID
};

class CCollider;

// 충돌체 및 충돌 관리 클래스
class CCollisionManager
{
	SINGLETON(CCollisionManager);
private:
	// 여러 그룹간의 충돌을 비트를 통해서 구분
	// ex) m_arrCheckGroup[eGroup_GameObj::Player] = 0000 0000 0000 1100 이라면
	// Player그룹은 3번째, 2번째 그룹과 충돌 가능하도록 체크
	UINT m_arrCheckGroup[(UINT)GROUP_GAMEOBJ::SIZE];

	// 충돌체 간의 이전 충돌 정보
	map<ULONGLONG, bool> m_mapCollisionInfo;

public:
	void init();
	void update();

	// 그룹간의 충돌 정보 업데이트
	// 두 그룹이 이전 업데이트에서 충돌 했는지 안했는지, 현재는 충돌 중인지 아닌지 업데이트 해줌
	void CollisionGroupUpdate(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);
	// 두 그룹이 충돌 했는지 안했는지 검사
	bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);

	// 충돌 검사를 해야할 오브젝트 체크
	void CheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);

	// 충돌 가능 체크가 되어있는 그룹들을 해제
	void UnCheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);

	// 모든 충돌체에 대해 충돌 체크 해제
	void Reset();
};

