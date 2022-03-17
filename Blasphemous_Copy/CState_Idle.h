#pragma once
#include "CState.h"
class CState_Idle : public CState
{
public:
	CState_Idle(ENEMY_STATE eState);
	~CState_Idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

