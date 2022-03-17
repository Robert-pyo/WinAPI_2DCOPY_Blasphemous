#pragma once
class AI;

class CState
{
	friend class AI;
private:
	CAI* m_pOwnerAI;
	ENEMY_STATE m_eEnmState;

public:
	CState(ENEMY_STATE eState);
	virtual ~CState();

	virtual void update() = 0;
	virtual void Enter() = 0;	// 각 상태마다 구현
	virtual void Exit() = 0;	// 각 상태마다 구현

	CAI* GetOwnerObj();
	ENEMY_STATE GetState();
};

