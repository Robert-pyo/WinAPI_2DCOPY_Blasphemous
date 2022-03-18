#include "framework.h"
#include "CState_Idle.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CEnemy.h"

CState_Idle::CState_Idle(ENEMY_STATE eState)
	: CState(ENEMY_STATE::IDLE)
{

}

CState_Idle::~CState_Idle()
{
}

void CState_Idle::update()
{
	CPlayer* pPlayer = CSceneManager::GetInst()->GetCurrentScene()->GetPlayer();
	fVector2D fvPlayerPos = pPlayer->GetPos();

	CEnemy* pEnemy = GetEnemy();
	fVector2D fvEnemyPos = pEnemy->GetPos();

	fVector2D fvDiff = fvPlayerPos - fvEnemyPos;
	float fLength = fvDiff.Length();

	if (fLength < pEnemy->GetEnemyInfo().fRecogRange)
	{
		// ���� ���� ���� EventManager�� ����Ǿ�� ������ ����ȭ ����
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
	}
}

void CState_Idle::Enter()
{
	
}

void CState_Idle::Exit()
{
}
