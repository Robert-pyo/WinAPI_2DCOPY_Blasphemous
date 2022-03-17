#pragma once
#include "CGameObject.h"
class CWeapon : public CGameObject
{
private:
	CGameObject* m_pOwner;

	float m_fAtk;		// °ø°Ý·Â

public:
	CWeapon();
	virtual ~CWeapon();

	virtual void update();
	virtual void render();

	CGameObject* GetOwnerObj();
	const float GetAtkValue();

	void SetOwnerObj(CGameObject* pOwner);
	void SetAtk(const float atk);

	virtual void Attack() = 0;

	virtual void OnCollision(CCollider* other);
};

