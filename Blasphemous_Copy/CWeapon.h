#pragma once
#include "CGameObject.h"
class CWeapon : public CGameObject
{
private:
	CGameObject* m_pOwner;

	float m_fAtt;			// 공격력
	float m_fAttDuration;	// 공격 시간

public:
	CWeapon();
	virtual ~CWeapon();

	virtual void update();
	virtual void render();

public:
	CGameObject* GetOwnerObj();
	void SetOwnerObj(CGameObject* pOwner);

	const float GetAttValue();
	void SetAtt(const float att);

	const float GetDuration();
	void SetAttDuration(const float duration);
public:
	virtual void Attack() = 0;

public:
	virtual void OnCollision(CCollider* other) {}
	virtual void OnCollisionEnter(CCollider* other) {}
	virtual void OnCollisionExit(CCollider* other) {}
};

