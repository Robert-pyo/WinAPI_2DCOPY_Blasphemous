#pragma once
#include "CState.h"
class CState_Attack : public CState
{
private:
	CEnemy* m_pEnemy;

	float m_fAttAccTime;

public:
	CState_Attack(ENEMY_STATE eEnmState);
	~CState_Attack();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

