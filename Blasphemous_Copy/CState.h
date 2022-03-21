#pragma once
#include "CAnimator.h"

class AI;
class CEnemy;

class CState
{
	friend class AI;
private:
	AI* m_pAI;
	ENEMY_STATE m_eEnmState;

public:
	CState(ENEMY_STATE eState);
	virtual ~CState();

public:
	virtual void update() = 0;
	virtual void Enter() = 0;	// �� ���¸��� ����	
	virtual void Exit() = 0;	// �� ���¸��� ����

public:
	AI* GetAI();
	ENEMY_STATE GetState();
	CEnemy* GetEnemy();
};

