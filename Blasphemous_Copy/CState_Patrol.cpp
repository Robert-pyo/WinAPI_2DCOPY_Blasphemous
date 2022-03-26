#include "framework.h"
#include "CState_Patrol.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CAnimation.h"
#include "CEnemy_Stoner.h"

CState_Patrol::CState_Patrol(ENEMY_STATE eState)
	:CState(eState)
{
	m_fMoveAccTime = 0.f;
	m_fvEnemyDir = {};
}

CState_Patrol::~CState_Patrol()
{
}

void CState_Patrol::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	fVector2D fvPlayerPos = pPlayer->GetPos();
	fVector2D fvEnemyPos = GetEnemy()->GetPos();

	float fLength = (fvPlayerPos - fvEnemyPos).Length();

	m_fMoveAccTime += fDeltaTime;
	if (m_fMoveAccTime >= 3.f)
	{
		if (m_fvEnemyDir == m_fvEnemyDir.Right())
			m_fvEnemyDir = m_fvEnemyDir.Left();
		else
			m_fvEnemyDir = m_fvEnemyDir.Right();

		m_fMoveAccTime = 0;
	}

	fvEnemyPos.x += m_fvEnemyDir.x * GetEnemy()->GetEnemyInfo().fVelocity * fDeltaTime;

	GetEnemy()->SetPos(fvEnemyPos);
	GetEnemy()->SetDir(m_fvEnemyDir);

	if (fLength < GetEnemy()->GetEnemyInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
	}
}

void CState_Patrol::Enter()
{
	m_fMoveAccTime = 0;
}

void CState_Patrol::Exit()
{
}
