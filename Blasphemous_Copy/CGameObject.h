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

	bool m_bIsActive;	// 오브젝트 현재 상태
	void SetDisable();	// 비활성화 상태로 만듦

	// Collider는 컴포넌트로써 존재한다.
	// 각 오브젝트는 Collider를 가질 수도, 가지지 않을 수도 있다.
	// 따라서 컴포넌트로 설정하여 상속으로 CGameObject를 부모클래스로 두더라도
	// collider를 사용하는 객체와 사용하지 않는 객체를 나눌 수 있다.
	CCollider* m_pCollider;

	// 애니메이터 컴포넌트
	CAnimator* m_pAnimator;

	GROUP_GAMEOBJ objGroup;

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() = 0;

	virtual void update() = 0;

	// collider는 모든 객체의 업데이트가 끝난 후 계산이 진행되어야 한다.
	// 만약 Player객체의 업데이트가 끝났더라도 서로 충돌 계산이 이루어져야할 enemy객체가 업데이트가 되지 않았다면
	// 서로 충돌하지 않았는데도 충돌되었다고 계산될 수 있으므로 꼭 모든 업데이트가 끝난 후 진행되어야한다.
	// 그러므로 충돌의 계산은 FinalUpdate()에서 진행한다.
	virtual void finalUpdate();	// CGameObject를 상속받은 클래스가 오버라이딩 하는 것을 막기 위해 final 키워드 삽입

	virtual void render(HDC hDC) = 0;

	virtual void component_render(HDC hDC);

	void initObject	(const fPoint m_fptPos, const fPoint m_fptScale);

	wstring GetName();
	fPoint	GetPos();
	fPoint	GetScale();
	bool	IsDisabled();
	// 객체가 소유하고있는 Collider를 반환한다.
	CCollider* GetCollider();
	CAnimator* GetAnimator();

	void	SetName(const wstring& name);
	void	SetPos(const fPoint& m_fptPos);
	void	SetScale(const fPoint& m_fptScale);

	void SetObjGroup(const GROUP_GAMEOBJ& type);
	GROUP_GAMEOBJ GetObjGroup();

	// 다른 곳에서 collider를 생성하는게 아닌 오브젝트 자신에서 생성해야 하므로
	// SetCollider가 아니라 CreateCollider로 명명
	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* target) {}
	virtual void OnCollisionEnter(CCollider* target) {}
	virtual void OnCollisionExit(CCollider* target) {}
};