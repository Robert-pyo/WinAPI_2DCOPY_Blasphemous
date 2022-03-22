#pragma once
#include "CWeapon.h"

class CD2DImage;
class CEffect_SwordSlash;

class CPlayerSword : public CWeapon
{
private:
	CD2DImage* m_pImg;

	float fAccTime;

	CEffect_SwordSlash* m_pFxSlash;

public:
	CPlayerSword();
	~CPlayerSword();

	virtual CPlayerSword* Clone();

	virtual void update();
	virtual void render();

	virtual void Attack();

public:
	void SetFX(CEffect_SwordSlash* fx) { m_pFxSlash = fx; }

public:
	virtual void OnCollision(CCollider* other);
	virtual void OnCollisionEnter(CCollider* other);
	virtual void OnCollisionExit(CCollider* other) {}
};

