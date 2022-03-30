#pragma once
#include "CState.h"
class CBossPatern_GroundSmash : public CState
{
private:
	float m_fAttAccTime;

public:
	CBossPatern_GroundSmash(ENEMY_STATE eEnmState);
	~CBossPatern_GroundSmash();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

