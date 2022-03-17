#include "framework.h"
#include "CState_Idle.h"

CState_Idle::CState_Idle(ENEMY_STATE eState)
	: CState(ENEMY_STATE::IDLE)
{

}

CState_Idle::~CState_Idle()
{
}

void CState_Idle::update()
{
}

void CState_Idle::Enter()
{
}

void CState_Idle::Exit()
{
}
