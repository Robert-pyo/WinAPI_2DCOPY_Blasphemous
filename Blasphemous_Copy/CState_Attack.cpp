#include "framework.h"
#include "CState_Attack.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CEnemy.h"
#include "CEnemy_Acolyte.h"
#include "CEnemy_Stoner.h"
#include "CWeapon.h"
#include "CAnimation.h"

CState_Attack::CState_Attack(ENEMY_STATE eEnmState)
	: CState(eEnmState)
{
	m_pEnemy = nullptr;
	m_fAttAccTime = 0.f;
}

CState_Attack::~CState_Attack()
{
}

void CState_Attack::update()
{
	m_fAttAccTime += fDeltaTime;

	m_pEnemy->Attack();

	if (m_pEnemy->GetAnimator()->GetCurAnim()->GetAnimDuration() < m_fAttAccTime)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
		m_pEnemy->SetAttCount(0);
		m_fAttAccTime = 0.f;
	}
}

void CState_Attack::Enter()
{
	m_fAttAccTime = 0.f;
	m_pEnemy = GetEnemy();
}

void CState_Attack::Exit()
{
	if (GetEnemy()->GetName() == L"Acolyte")
	{
		m_pEnemy = (CEnemy_Acolyte*)GetEnemy();
		m_pEnemy->SetVelocity(100.f);
	}
}
