#pragma once
#include "CWeapon.h"

class CEffect_Spear;

class CSpear : public CWeapon
{
private:
	CEffect_Spear* m_pFx;

public:
	CSpear();
	~CSpear();

	virtual CSpear* Clone();

	virtual void update();
	virtual void render();

	virtual void Attack();
};

