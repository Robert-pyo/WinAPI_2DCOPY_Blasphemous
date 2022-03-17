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
			delete iter->second;
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
}

