#include "framework.h"
#include "CEnemy_Stoner.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CEffect_Rock.h"

CEnemy_Stoner::CEnemy_Stoner()
{
	SetImage(L"Stoner", L"texture\\Enemy\\Stoner\\stoner_anim_merge.png");

	SetName(L"Stoner");
	SetScale(fPoint(70.f, 50.f));
	m_fAtkAccTime = 0.f;

	tEnemyInfo info = {};
	info.fHP = 100.f;
	info.fAtt = 15.f;
	info.fAttRange = 1000.f;
	info.fAttDelayTime = 3.f;
	info.fRecogRange = 1000.f;
	info.fVelocity = 0.f;
	info.fInvTime = 0.1f;
	info.iMoney = 20;
	info.pWeapon = nullptr;
	SetEnemyInfo(info);

	CreateCollider();
	GetCollider()->SetScale(fPoint(140.f, 90.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 30.f));

	Init_Animation();
}

CEnemy_Stoner::~CEnemy_Stoner()
{
}

CEnemy_Stoner* CEnemy_Stoner::Clone()
{
	return new CEnemy_Stoner(*this);
}

void CEnemy_Stoner::update()
{
	CEnemy::update();

	Update_Animation();

	GetAnimator()->update();
}

void CEnemy_Stoner::render()
{
	component_render();
}

void CEnemy_Stoner::Update_Animation()
{
	if (GetAI()->GetPrevState() != nullptr && 
		GetAI()->GetCurState()->GetState() == GetAI()->GetPrevState()->GetState())
		return;

	switch (GetAI()->GetCurState()->GetState())
	{
	case ENEMY_STATE::IDLE:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->FindAnimation(L"Stoner_Idle_R")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Idle_R");
		}
		else
		{
			GetAnimator()->FindAnimation(L"Stoner_Idle_L")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Idle_L");
		}
	}break;
	case ENEMY_STATE::TRACE:
	{
		if (GetAI()->GetPrevState()->GetState() == ENEMY_STATE::PATROL)
		{
			GetAnimator()->FindAnimation(L"Stoner_Rising_R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Stoner_Rising_L")->SetFrame(0);

			if (GetDir().x > 0.f)
			{
				GetAnimator()->Play(L"Stoner_Rising_R");
			}
			else
			{
				GetAnimator()->Play(L"Stoner_Rising_L");
			}
		}
		else
		{
			if (GetDir().x > 0.f)
			{
				GetAnimator()->Play(L"Stoner_Idle_R");
			}
			else
			{
				GetAnimator()->Play(L"Stoner_Idle_L");
			}
		}
	}break;
	case ENEMY_STATE::PATROL:
	{
		GetAnimator()->FindAnimation(L"Stoner_Hide")->SetFrame(0);
		GetAnimator()->Play(L"Stoner_Hide");
	}break;
	case ENEMY_STATE::ATTACK:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->FindAnimation(L"Stoner_Attack_R")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Attack_R");
		}
		else
		{
			GetAnimator()->FindAnimation(L"Stoner_Attack_L")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Attack_L");
		}
	}break;
	case ENEMY_STATE::HIT:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->FindAnimation(L"Stoner_Hurt_R")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Hurt_R");
		}
		else
		{
			GetAnimator()->FindAnimation(L"Stoner_Hurt_L")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Hurt_L");
		}
	}break;
	case ENEMY_STATE::DEAD:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->FindAnimation(L"Stoner_Death_R")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Death_R");
		}
		else
		{
			GetAnimator()->FindAnimation(L"Stoner_Death_L")->SetFrame(0);
			GetAnimator()->Play(L"Stoner_Death_L");
		}
	}break;

	default:
		break;
	}

	GetAI()->SetPrevState(GetAI()->GetCurState()->GetState());
}

void CEnemy_Stoner::Init_Animation()
{
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Stoner_Hide", GetImage(), fPoint(968.f, 810.f), fPoint(121.f, 81.f), fPoint(0.f, -81.f), 0, 0.07f, 11, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Rising_R", GetImage(), fPoint(968.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 11, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Rising_L", GetImage(), fPoint(847.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 11, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Idle_R", GetImage(), fPoint(726.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 12, true, false);
	GetAnimator()->CreateAnimation(L"Stoner_Idle_L", GetImage(), fPoint(605.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 12, true, false);
	GetAnimator()->CreateAnimation(L"Stoner_Hurt_R", GetImage(), fPoint(484.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 6, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Hurt_L", GetImage(), fPoint(363.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 6, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Death_R", GetImage(), fPoint(242.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 16, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Death_L", GetImage(), fPoint(242.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 16, false, true);
	GetAnimator()->CreateAnimation(L"Stoner_Attack_R", GetImage(), fPoint(121.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 20, false, false);
	GetAnimator()->CreateAnimation(L"Stoner_Attack_L", GetImage(), fPoint(0.f, 0.f), fPoint(121.f, 81.f), fPoint(0.f, 81.f), 0, 0.07f, 20, false, false);
}

void CEnemy_Stoner::Attack()
{
	if (GetAttCount() == 0)
	{
		float fAttStartTime = GetAnimator()->GetCurAnim()->GetFrame(0).fDuration * 16;

		m_fAtkAccTime += fDeltaTime;

		if (fAttStartTime <= m_fAtkAccTime)
		{
			CEffect_Rock* fxRock = new CEffect_Rock;
			fxRock->SetOwnerObj(this);
			fxRock->SetPos(GetPos());
			fxRock->init();
			CreateObj(fxRock, GROUP_GAMEOBJ::ENEMY_ATT_FX);

			SetAttCount(1);
			m_fAtkAccTime = 0;
		}
	}
}
