#pragma once
#include "CWeapon.h"
class CPlayerSword : public CWeapon
{
private:
	float m_fAttTime;	// 공격 시간

public:
	CPlayerSword();
	~CPlayerSword();

	virtual CPlayerSword* Clone();

	virtual void update();
	virtual void render();

	virtual void Attack();


};

