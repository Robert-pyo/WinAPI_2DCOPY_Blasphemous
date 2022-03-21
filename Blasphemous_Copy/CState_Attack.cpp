#include "framework.h"
#include "CState_Attack.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CEnemy.h"
#include "CEnemy_Acolyte.h"
#include "CWeapon.h"
#include "CAnimation.h"

CState_Attack::CState_Attack(ENEMY_STATE eEnmState)
	: CState(eEnmState)
{
	m_pEnemy = nullptr;
}

CState_Attack::~CState_Attack()
{
}

void CState_Attack::update()
{
	static float fTime = 0.f;
	fTime += fDeltaTime;

	m_pEnemy->Attack();

	if (m_pEnemy->GetEnemyInfo().pWeapon->GetDuration() < fTime)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
		m_pEnemy->SetAttCount(0);
		fTime = 0.f;
	}
}

void CState_Attack::Enter()
{
	if (GetEnemy()->GetName() == L"Acolyte")
	{
		m_pEnemy = (CEnemy_Acolyte*)GetEnemy();
		m_pEnemy->SetAttCount(1);
		m_pEnemy->GetAnimator()->FindAnimation(L"Acolyte_Attack_R")->SetFrame(0);
		m_pEnemy->GetAnimator()->FindAnimation(L"Acolyte_Attack_L")->SetFrame(0);
		m_pEnemy->SetVelocity(500.f);
	}
}

void CState_Attack::Exit()
{
	if (GetEnemy()->GetName() == L"Acolyte")
	{
		m_pEnemy = (CEnemy_Acolyte*)GetEnemy();
		m_pEnemy->SetVelocity(100.f);
	}
}
