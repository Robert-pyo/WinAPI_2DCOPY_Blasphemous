#include "framework.h"
#include "CEnemyFactory.h"
#include "CEnemy.h"
#include "AI.h"
#include "CState_Idle.h"
#include "CState_Trace.h"
#include "CState_Attack.h"
#include "CEnemy_Acolyte.h"

CEnemy* CEnemyFactory::CreateEnemy(ENEMY_TYPE eEnmType, fPoint pos)
{
	CEnemy* pEnemy = nullptr;

	switch (eEnmType)
	{
	case ENEMY_TYPE::NORMAL:
	{
		pEnemy = new CEnemy_Acolyte;
		pEnemy->SetPos(pos);

		AI* pAI = new AI;
		pAI->AddState(new CState_Idle(ENEMY_STATE::IDLE));
		pAI->AddState(new CState_Trace(ENEMY_STATE::TRACE));
		pAI->AddState(new CState_Attack(ENEMY_STATE::ATTACK));
		//pAI->AddState(new CState_Hit(ENEMY_STATE::HIT));
		pAI->SetCurState(ENEMY_STATE::IDLE);

		pEnemy->SetAI(pAI);
	}
		break;
		
	case ENEMY_TYPE::RANGE:
		break;

	case ENEMY_TYPE::BOSS:
		break;

	default:
		break;
	}

	return pEnemy;
}
