#pragma once
#include "CState.h"
class CState_Sleep : public CState
{
private:
	bool m_bIsCutScenePlayed;

public:
	CState_Sleep(ENEMY_STATE eState);
	~CState_Sleep();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

