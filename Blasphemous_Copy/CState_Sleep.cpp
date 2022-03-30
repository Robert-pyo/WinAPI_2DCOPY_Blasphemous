#include "framework.h"
#include "CState_Sleep.h"
#include "CEnemy.h"

CState_Sleep::CState_Sleep(ENEMY_STATE eState)
	: CState(eState)
{
	m_bIsCutScenePlayed = false;
}

CState_Sleep::~CState_Sleep()
{
}

void CState_Sleep::update()
{
	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"BossCutScene")
	{
		m_bIsCutScenePlayed = true;
	}
	else
	{
		m_bIsCutScenePlayed = false;
	}

	if (!CGameManager::GetInst()->IsDisableControl() && m_bIsCutScenePlayed)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::IDLE);
	}
}

void CState_Sleep::Enter()
{
}

void CState_Sleep::Exit()
{
}
