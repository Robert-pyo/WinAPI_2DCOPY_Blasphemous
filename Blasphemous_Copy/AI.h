#pragma once
class CEnemy;
class CState;

class AI
{
	friend class CEnemy;

private:
	map<ENEMY_STATE, CState*>  m_mapEnmState;
	CEnemy* m_pOwner;
	CState* m_pCurState;

public:
	AI();
	~AI();

public:
	void update();

public:
	void AddState(CState* pState);
	CState* GetState(ENEMY_STATE eEnmState);
	void SetCurState(ENEMY_STATE eEnmState);
	void ChangeState(ENEMY_STATE eNextState);

	CEnemy* GetOwnerObj() { return m_pOwner; }
};