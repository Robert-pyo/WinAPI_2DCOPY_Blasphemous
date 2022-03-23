#include "framework.h"
#include "CState_Trace.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CScene.h"

CState_Trace::CState_Trace(ENEMY_STATE eEnmState)
	:CState(eEnmState)
{
}

CState_Trace::~CState_Trace()
{
}

void CState_Trace::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	fVector2D fvPlayerPos = pPlayer->GetPos();
	fVector2D fvEnemyPos = GetEnemy()->GetPos();

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

	static float fAttAccTime = 0.f;
	fAttAccTime += fDeltaTime;
	if (fLength < GetEnemy()->GetEnemyInfo().fAttRange && GetEnemy()->GetEnemyInfo().iAttCount == 0
		&& GetEnemy()->GetEnemyInfo().fAttDelayTime <= fAttAccTime)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::ATTACK);
		fAttAccTime = 0.f;
	}
}

void CState_Trace::Enter()
{
}

void CState_Trace::Exit()
{
}
