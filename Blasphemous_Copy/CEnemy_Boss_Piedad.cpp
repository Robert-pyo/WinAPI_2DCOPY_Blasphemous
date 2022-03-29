#include "framework.h"
#include "CEnemy_Boss_Piedad.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEnemy_Boss_Piedad::CEnemy_Boss_Piedad()
{
	SetName(L"Piedad");
	SetScale(fPoint(80.f, 130.f));
	m_fAtkAccTime = 0.f;

	tEnemyInfo info = {};
	info.fHP = 1000.f;
	info.fAtt = 20.f;
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

CEnemy_Boss_Piedad::~CEnemy_Boss_Piedad()
{
}

CEnemy_Boss_Piedad* CEnemy_Boss_Piedad::Clone()
{
	return nullptr;
}

void CEnemy_Boss_Piedad::update()
{
	Update_Animation();

	GetAnimator()->update();

	if (GetAI()->GetCurState()->GetState() == ENEMY_STATE::SLEEP)
	{
		if (GetAnimator()->FindAnimation(L"Piedad_CutScene")->IsAnimDone())
		{
			GetAnimator()->Play(L"Piedad_CutScene2");
		}
		return;
	}

	CEnemy::update();
}

void CEnemy_Boss_Piedad::render()
{
	component_render();
}

void CEnemy_Boss_Piedad::Update_Animation()
{
	if (GetAI()->GetPrevState() != nullptr &&
		GetAI()->GetCurState()->GetState() == GetAI()->GetPrevState()->GetState())
		return;

	switch (GetAI()->GetCurState()->GetState())
	{
	case ENEMY_STATE::SLEEP:
	{
		GetAnimator()->Play(L"Piedad_CutScene");
	}break;
	case ENEMY_STATE::IDLE:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->FindAnimation(L"Piedad_Idle_Right")->SetFrame(0);
			GetAnimator()->Play(L"Piedad_Idle_Right");
		}
		else
		{
			GetAnimator()->FindAnimation(L"Piedad_Idle_Left")->SetFrame(0);
			GetAnimator()->Play(L"Piedad_Idle_Left");
		}
	}break;
	case ENEMY_STATE::TRACE:
	{
		GetAnimator()->FindAnimation(L"Piedad_Walk_Left")->SetFrame(0);
		GetAnimator()->FindAnimation(L"Piedad_Walk_Right")->SetFrame(0);

		if (GetDir().x > 0.f)
		{
			GetAnimator()->Play(L"Piedad_Walk_Right");
		}
		else
		{
			GetAnimator()->Play(L"Piedad_Walk_Left");
		}
	}break;
	case ENEMY_STATE::DEAD:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->FindAnimation(L"Piedad_Death_Right")->SetFrame(0);
			GetAnimator()->Play(L"Piedad_Death_Right");
		}
		else
		{
			GetAnimator()->FindAnimation(L"Piedad_Death_Left")->SetFrame(0);
			GetAnimator()->Play(L"Piedad_Death_Left");
		}
	}break;

	default:
		break;
	}

	GetAI()->SetPrevState(GetAI()->GetCurState()->GetState());
}

void CEnemy_Boss_Piedad::Init_Animation()
{
#pragma region AnimationRegistration

	SetImage(L"Piedad_CutScene", L"texture\\Enemy\\Piedad\\CutScene\\pietat_boss_sprite_sheet_part_1.png");
	m_pCutScenePart2 = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_CutScene2", L"texture\\Enemy\\Piedad\\CutScene\\pietat_boss_sprite_sheet_part_2.png");

	m_pIdleImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Idle", L"texture\\Enemy\\Piedad\\Idle\\Pietat_Idle_Anim.png");

	m_pWalkImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Walk", L"texture\\Enemy\\Piedad\\Walk\\pietat_walk_anim.png");
	m_pWalkToIdleImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Walk", L"texture\\Enemy\\Piedad\\Walk\\pietat_walk_to_idle_anim.png");

	m_pGroundSmashImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_GroundSmash", L"texture\\Enemy\\Piedad\\GroundSmash\\Pietat_GroundSmash_Right.png");

	m_pSlashImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Slash", L"texture\\Enemy\\Piedad\\Slash\\pietat_slash_anim.png");

	m_pSpitImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Spit", L"texture\\Enemy\\Piedad\\Spit\\pietat_spit_loop_anim.png");
	m_pSpitBackIdleImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_SpitBackIdle", L"texture\\Enemy\\Piedad\\Spit\\pietat_spit_back_to_idle_anim.png");
	m_pSpitStartImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_SpitStart", L"texture\\Enemy\\Piedad\\Spit\\pietat_spit_start_anim.png");

	m_pStompImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Stomp", L"texture\\Enemy\\Piedad\\Stomp\\pietat_stomp_anim.png");

	m_pTurnAroundImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Turn", L"texture\\Enemy\\Piedad\\TurnAround\\pietat_turnaround_anim.png");

	m_pDeathImg = CResourceManager::GetInst()->LoadD2DImage(
		L"Piedad_Death", L"texture\\Enemy\\Piedad\\Death\\pietat_death_anim.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Piedad_CutScene",
		GetImage(), fPoint(12.f, 32.f), fPoint(260.f, 286.f), fPoint(260.f, 0.f), 8, 0.3f, 48, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_CutScene2",
		m_pCutScenePart2, fPoint(0.f, 0.f), fPoint(500.f, 272.f), fPoint(500.f, 0.f), 10, 0.1f, 39, false, false);

	GetAnimator()->CreateAnimation(L"Piedad_Idle_Right",
		m_pIdleImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 5, 0.05f, 13, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_Idle_Left",
		m_pIdleImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 5, 0.05f, 13, false, true);


	GetAnimator()->CreateAnimation(L"Piedad_Walk_Right",
		m_pWalkImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 4, 0.05f, 16, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_Walk_Left",
		m_pWalkImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 4, 0.05f, 16, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_WalkToIdle_Right",
		m_pWalkToIdleImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 5, 0.05f, 10, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_WalkToIdle_Left",
		m_pWalkToIdleImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 5, 0.05f, 10, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_GroundSmash_Right",
		m_pGroundSmashImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 10, 0.05f, 50, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_GroundSmash_Left",
		m_pGroundSmashImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 10, 0.05f, 50, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_Slash_Right",
		m_pSlashImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 10, 0.05f, 52, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_Slash_Left",
		m_pSlashImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 10, 0.05f, 52, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_SpitLoop_Right",
		m_pSpitImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 10, 0.05f, 15, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_SpitLoop_Left",
		m_pSpitImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 10, 0.05f, 15, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_SpitBackToIdle_Right",
		m_pSpitBackIdleImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 0, 0.05f, 5, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_SpitBackToIdle_Left",
		m_pSpitBackIdleImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 0, 0.05f, 5, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_SpitStart_Right",
		m_pSpitStartImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 0, 0.05f, 10, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_SpitStart_Left",
		m_pSpitStartImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 0, 0.05f, 10, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_Stomp_Right",
		m_pStompImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 7, 0.05f, 19, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_Stomp_Left",
		m_pStompImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 7, 0.05f, 19, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_Turn_Right",
		m_pTurnAroundImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 5, 0.05f, 13, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_Turn_Left",
		m_pTurnAroundImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 5, 0.05f, 13, false, true);

	GetAnimator()->CreateAnimation(L"Piedad_Death_Right",
		m_pDeathImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 7, 0.05f, 37, false, false);
	GetAnimator()->CreateAnimation(L"Piedad_Death_Left",
		m_pDeathImg, fPoint(0.f, 0.f), fPoint(382.f, 300.f), fPoint(382.f, 0.f), 7, 0.05f, 37, false, true);

#pragma endregion

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"Piedad_CutScene");
	for (int i = 0; i < 48; ++i)
	{
		pAnim->GetFrame(i).fptOffset.y -= 16.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Piedad_CutScene2");
	for (int i = 0; i < 39; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 7.f;
		pAnim->GetFrame(i).fptOffset.y -= 67.f;
	}
}

void CEnemy_Boss_Piedad::Attack()
{
}
