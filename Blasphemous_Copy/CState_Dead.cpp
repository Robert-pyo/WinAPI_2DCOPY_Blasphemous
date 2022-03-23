#include "framework.h"
#include "CState_Dead.h"
#include "CEnemy.h"
#include "CAnimator.h"
#include "CAnimation.h"

CState_Dead::CState_Dead(ENEMY_STATE eState)
	: CState(eState)
{
}

CState_Dead::~CState_Dead()
{
}

void CState_Dead::update()
{
	if (GetEnemy()->GetAnimator()->GetCurAnim()->IsAnimDone())
	{
		DeleteObj(GetEnemy());
	}
}

void CState_Dead::Enter()
{
}

void CState_Dead::Exit()
{
}
