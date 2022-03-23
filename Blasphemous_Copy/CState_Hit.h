#pragma once
#include "CState.h"
class CState_Hit : public CState
{
public:
	CState_Hit(ENEMY_STATE eState);
	~CState_Hit();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

