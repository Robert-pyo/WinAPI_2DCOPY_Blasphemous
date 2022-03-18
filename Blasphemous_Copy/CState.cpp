#include "framework.h"
#include "CState.h"
#include "AI.h"
#include "CEnemy.h"

CState::CState(ENEMY_STATE eState)
{
	m_eEnmState = eState;
	m_pAI = nullptr;
}

CState::~CState()
{
	int a = 0;
}

AI* CState::GetAI()
{
	return m_pAI;
}

ENEMY_STATE CState::GetState()
{
	return m_eEnmState;
}

CEnemy* CState::GetEnemy()
{
	return m_pAI->GetOwnerObj();
}

