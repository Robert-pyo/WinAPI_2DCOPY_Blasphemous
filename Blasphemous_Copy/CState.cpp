#include "framework.h"
#include "CState.h"

CState::CState(ENEMY_STATE eState)
{
	m_eEnmState = eState;
	m_pOwnerAI = nullptr;
}

CState::~CState()
{
}

CAI* CState::GetOwnerObj()
{
	return m_pOwnerAI;
}

ENEMY_STATE CState::GetState()
{
	return m_eEnmState;
}
