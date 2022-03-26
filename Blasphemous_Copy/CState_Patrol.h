#pragma once
#include "CState.h"
class CState_Patrol : public CState
{
private:
	float m_fMoveAccTime;
	fVector2D m_fvEnemyDir;
public:
	CState_Patrol(ENEMY_STATE eState);
	~CState_Patrol();

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

