#include "framework.h"
#include "CState_Attack.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CEnemy.h"
#include "CEnemy_Acolyte.h"
#include "CEnemy_Stoner.h"
#include "CWeapon.h"
#include "CAnimation.h"
#include "CCollider.h"

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

	CPlayer* pPlayer = CPlayer::GetPlayer();

	float fvPlayerCenterX = (float)pPlayer->GetCollider()->GetBorderPos().left + pPlayer->GetCollider()->GetScale().x / 2.f;
	float fvPlayerCenterY = (float)pPlayer->GetCollider()->GetBorderPos().top + pPlayer->GetCollider()->GetScale().y / 2.f;

	fVector2D fvPlayerPos = fVector2D(fvPlayerCenterX, fvPlayerCenterY);
	fVector2D fvEnemyPos = GetEnemy()->GetPos();

	CEnemy* pEnemy = GetEnemy();
	fVector2D fvEnemyDir = fvPlayerPos - fvEnemyPos;
	float fLength = fvEnemyDir.Length();
	fvEnemyDir.Normalize();

	if (m_pEnemy->GetName() == L"Piedad")
	{
		if (fLength < m_pEnemy->GetEnemyInfo().fAttRange / 2)
		{
			ChangeAIState(GetAI(), ENEMY_STATE::BOSSPATERN1);
		}
		return;
	}

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
