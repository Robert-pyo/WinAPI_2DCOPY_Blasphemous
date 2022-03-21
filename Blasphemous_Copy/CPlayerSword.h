#pragma once
#include "CWeapon.h"

class CD2DImage;

class CPlayerSword : public CWeapon
{
private:
	CD2DImage* m_pImg;

	float fAccTime;

public:
	CPlayerSword();
	~CPlayerSword();

	virtual CPlayerSword* Clone();

	virtual void update();
	virtual void render();

	virtual void Attack();

	virtual void OnCollision(CCollider* other);
	virtual void OnCollisionEnter(CCollider* other);
	virtual void OnCollisionExit(CCollider* other) {}
};

