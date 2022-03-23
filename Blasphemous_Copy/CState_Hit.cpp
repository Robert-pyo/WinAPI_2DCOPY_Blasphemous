#include "framework.h"
#include "CState_Hit.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CAnimator.h"
#include "CAnimation.h"

CState_Hit::CState_Hit(ENEMY_STATE eState)
	: CState(eState)
{
}

CState_Hit::~CState_Hit()
{
}

static float fHitAccTime;

void CState_Hit::update()
{
	fHitAccTime += fDeltaTime;
	
	if (GetEnemy()->GetEnemyInfo().fInvTime <= fHitAccTime)
	{
		// 무적시간이 끝났으면 trace 상태로 전환
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
		fHitAccTime = 0.f;
		GetEnemy()->SetInvincible(false);
	}
}

void CState_Hit::Enter()
{
	fHitAccTime = 0.f;
	GetEnemy()->SetInvincible(true);
	
	if (L"Acolyte" == GetEnemy()->GetName())
	{
		GetEnemy()->GetAnimator()->FindAnimation(L"Acolyte_Hit_R")->SetFrame(0);
		GetEnemy()->GetAnimator()->FindAnimation(L"Acolyte_Hit_L")->SetFrame(0);
	}
}

void CState_Hit::Exit()
{
}
