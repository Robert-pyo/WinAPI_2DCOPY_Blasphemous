#pragma once
#include "CWeapon.h"
class CPlayerSword : public CWeapon
{
private:
	float m_fAttTime;	// ���� �ð�

public:
	CPlayerSword();
	~CPlayerSword();

	virtual CPlayerSword* Clone();

	virtual void update();
	virtual void render();

	virtual void Attack();


};

