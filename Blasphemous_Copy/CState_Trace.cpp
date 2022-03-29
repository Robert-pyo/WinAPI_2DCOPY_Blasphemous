#include "framework.h"
#include "CState_Trace.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CScene.h"
#include "CCollider.h"

CState_Trace::CState_Trace(ENEMY_STATE eEnmState)
	:CState(eEnmState)
{
	m_fAttAccTime = 0.f;
}

CState_Trace::~CState_Trace()
{
}

void CState_Trace::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();

	float fvPlayerCenterX = (float)pPlayer->GetCollider()->GetBorderPos().left + pPlayer->GetCollider()->GetScale().x / 2.f;
	float fvPlayerCenterY = (float)pPlayer->GetCollider()->GetBorderPos().top + pPlayer->GetCollider()->GetScale().y / 2.f;

	fVector2D fvPlayerPos = fVector2D(fvPlayerCenterX, fvPlayerCenterY);
	fVector2D fvEnemyPos = GetEnemy()->GetPos();

	CEnemy* pEnemy = GetEnemy();
	fVector2D fvEnemyDir = fvPlayerPos - fvEnemyPos;
	float fLength = fvEnemyDir.Length();
	fvEnemyDir.Normalize();

	fvEnemyPos.x += fvEnemyDir.x * GetEnemy()->GetEnemyInfo().fVelocity * fDeltaTime;

	GetEnemy()->SetPos(fvEnemyPos);
	GetEnemy()->SetDir(fvEnemyDir);

	if (fLength > GetEnemy()->GetEnemyInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::IDLE);
	}
	else if (pPlayer->GetCollider()->GetBorderPos().bottom < pEnemy->GetCollider()->GetBorderPos().top)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::IDLE);
	}

	m_fAttAccTime += fDeltaTime;
	if (fLength < GetEnemy()->GetEnemyInfo().fAttRange && GetEnemy()->GetEnemyInfo().iAttCount == 0
		&& GetEnemy()->GetEnemyInfo().fAttDelayTime <= m_fAttAccTime)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::ATTACK);
		m_fAttAccTime = 0.f;
	}
}

void CState_Trace::Enter()
{
	GetEnemy()->SetVelocity(GetEnemy()->GetEnemyInfo().fMaxVelocity);
}

void CState_Trace::Exit()
{
}
