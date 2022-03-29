#pragma once
#include "CState.h"
class CState_Trace : public CState
{
private:
	float m_fAttAccTime;
public:
	CState_Trace(ENEMY_STATE eEnmState);
	~CState_Trace();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

