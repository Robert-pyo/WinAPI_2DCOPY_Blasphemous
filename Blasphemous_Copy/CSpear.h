#pragma once
#include "CWeapon.h"
class CSpear : public CWeapon
{
public:
	CSpear();
	~CSpear();

	virtual CSpear* Clone();

	virtual void update();
	virtual void render();

	virtual void Attack();
};

