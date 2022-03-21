#include "framework.h"
#include "CState.h"
#include "AI.h"

AI::AI()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

AI::~AI()
{
	if (!m_mapEnmState.empty())
	{
		for (map<ENEMY_STATE, CState*>::iterator iter = m_mapEnmState.begin(); iter != m_mapEnmState.end(); ++iter)
		{
			if (nullptr != iter->second)
			{
				delete iter->second;
			}
		}
		m_mapEnmState.clear();
	}
}

void AI::update()
{
	m_pCurState->update();
}

void AI::AddState(CState* pState)
{
	CState* pTargetState = GetState(pState->GetState());
	assert(!pTargetState);

	m_mapEnmState.insert(make_pair(pState->GetState(), pState));
	pState->m_pAI = this;
}

CState* AI::GetState(ENEMY_STATE eEnmState)
{
	map<ENEMY_STATE, CState*>::iterator iter = m_mapEnmState.find(eEnmState);

	// 일치하는 상태가 없다면 nullptr 반환
	if (m_mapEnmState.end() == iter)
		return nullptr;
	
	return iter->second;
}

CState* AI::GetCurState()
{
	return m_pCurState;
}

void AI::SetCurState(ENEMY_STATE eEnmState)
{
	m_pCurState = GetState(eEnmState);
	
	// m_pCurState에 nullptr이 들어갔다면 assert
	assert(m_pCurState);
}

void AI::ChangeState(ENEMY_STATE eNextState)
{
	CState* pNextState = GetState(eNextState);
	assert(m_pCurState != pNextState);

	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}

