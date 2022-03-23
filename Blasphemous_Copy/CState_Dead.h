#pragma once
#include "CState.h"
class CState_Dead : public CState
{
public:
	CState_Dead(ENEMY_STATE eState);
	~CState_Dead();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

