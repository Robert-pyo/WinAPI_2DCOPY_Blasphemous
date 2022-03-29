#pragma once
#include "CState.h"
class CState_Sleep : public CState
{
public:
	CState_Sleep(ENEMY_STATE eState);
	~CState_Sleep();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

