#pragma once

class CGameObject;

// 충돌체 컴포넌트
class CCollider
{
	friend CGameObject;
private:
	// Collider 정적 ID -> 모든 collider 공유
	static UINT s_iUID;

	// Collider 소유 오브젝트
	CGameObject* m_pOwner;

	// Collider의 위치
	fPoint m_fptFinalPos;

	// Collider가 오브젝트의 중심으로부터
	// 어느방향으로 얼마나 떨어져있는지 조정하기 위한 Offset
	fPoint m_fptOffsetPos;

	// Collider의 LeftTopRightBottom을 저장하기위한 변수
	RECT m_rtCollider;

	// Collider의 크기
	fPoint m_fptScale;

	// Collider 고유 아이디 -> 정적 ID를 기준으로 collider 추가 될때마다 1씩 증가
	UINT m_iUID;

	// 충돌 카운트
	UINT m_iCollisionCount;

public:
	CCollider	();
	~CCollider	();
	CCollider(const CCollider& other);

	fPoint	GetFinalPos		();
	fPoint	GetOffsetPos	();
	fPoint	GetScale		();
	RECT	GetBorderPos	();
	
	// 충돌체 고유 ID 반환
	UINT GetID();

	void SetFinalPos	(fPoint m_fptPos);
	void SetOffsetPos	(fPoint offset);
	void SetScale		(fPoint m_fptScale);

	void finalUpdate();
	void render();

	CGameObject* GetOwnerObj();

	// 충돌체 주인이 충돌에 대한 처리를 각각 다르게 처리할 수 있도록 함 ↓

	void OnCollision(CCollider* target);
	void OnCollisionEnter(CCollider* target);
	void OnCollisionExit(CCollider* target);
};

