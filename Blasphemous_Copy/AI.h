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

	void update();

	void AddState(CState* pState);
};