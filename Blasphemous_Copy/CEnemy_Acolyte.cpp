#include "framework.h"
#include "CEnemy_Acolyte.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CWeapon.h"
#include "CScene.h"
#include "CSpear.h"

CEnemy_Acolyte::CEnemy_Acolyte()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Acolyte", L"texture\\Enemy\\Acolyte\\Acolyte_merge.png");

	SetName(L"Acolyte");
	SetScale(fPoint(82.f, 232.f));
	m_bIsAttacking = false;
	m_fAtkAccTime = 0.f;

	tEnemyInfo info = {};
	info.fHP = 150.f;
	info.fAtt = 20.f;
	info.fAttRange = 300.f;
	info.fAttDelayTime = 2.f;
	info.fRecogRange = 400.f;
	info.fVelocity = 100.f;
	info.fInvTime = 0.1f;
	info.iMoney = 20;

	info.pWeapon = new CSpear;
	info.pWeapon->SetOwnerObj(this);
	info.pWeapon->SetPos(GetPos());
	SetEnemyInfo(info);

	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 100.f));
	GetCollider()->SetOffsetPos(fPoint(-20.f, 65.f));

	Init_Animation();
}

CEnemy_Acolyte::~CEnemy_Acolyte()
{
}

CEnemy_Acolyte* CEnemy_Acolyte::Clone()
{
	return nullptr;
}

void CEnemy_Acolyte::update()
{
	CEnemy::update();

	Update_Animation();

	GetAnimator()->update();
}

void CEnemy_Acolyte::render()
{
	component_render();
}

void CEnemy_Acolyte::Update_Animation()
{
	switch (GetAI()->GetCurState()->GetState())
	{
	case ENEMY_STATE::IDLE:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->Play(L"Acolyte_Idle_R");
		}
		else
		{
			GetAnimator()->Play(L"Acolyte_Idle_L");
		}
	}break;
	case ENEMY_STATE::TRACE:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->Play(L"Acolyte_Walk_R");
		}
		else
		{
			GetAnimator()->Play(L"Acolyte_Walk_L");
		}
	}break;
	case ENEMY_STATE::ATTACK:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->Play(L"Acolyte_Attack_R");
		}
		else
		{
			GetAnimator()->Play(L"Acolyte_Attack_L");
		}
	}break;
	case ENEMY_STATE::HIT:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->Play(L"Acolyte_Hit_R");
		}
		else
		{
			GetAnimator()->Play(L"Acolyte_Hit_L");
		}
	}break;
	case ENEMY_STATE::DEAD:
	{
		if (GetDir().x > 0.f)
		{
			GetAnimator()->Play(L"Acolyte_Death_R");
		}
		else
		{
			GetAnimator()->Play(L"Acolyte_Death_L");
		}
	}break;

	default:
		break;
	}
}

void CEnemy_Acolyte::Init_Animation()
{
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Acolyte_Idle_R", m_pImg, fPoint(0.f, 133.f), fPoint(41.f, 122.f), fPoint(42.f, 0.f), 0, 0.05f, 13, true, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Idle_L", m_pImg, fPoint(0.f, 133.f), fPoint(41.f, 122.f), fPoint(42.f, 0.f), 0, 0.05f, 13, true, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Walk_R", m_pImg, fPoint(560.f, 131.f), fPoint(45.f, 129.f), fPoint(45.f, 0.f), 0, 0.05f, 15, true, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Walk_L", m_pImg, fPoint(560.f, 131.f), fPoint(45.f, 129.f), fPoint(45.f, 0.f), 0, 0.05f, 15, true, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Hit_R", m_pImg, fPoint(1010.f, 260.f), fPoint(83.f, 117.f), fPoint(83.f, 0.f), 0, 0.08f, 12, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Hit_L", m_pImg, fPoint(1010.f, 260.f), fPoint(83.f, 117.f), fPoint(83.f, 0.f), 0, 0.08f, 12, false, true);
	GetAnimator()->CreateAnimation(L"Acolyte_ParryReact_R", m_pImg, fPoint(1008.f, 377.f), fPoint(168.f, 111.f), fPoint(168.f, 0.f), 0, 0.05f, 5, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_ParryReact_L", m_pImg, fPoint(1008.f, 377.f), fPoint(168.f, 111.f), fPoint(168.f, 0.f), 0, 0.05f, 5, false, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Death_R", m_pImg, fPoint(0.f, 0.f), fPoint(114.f, 131.f), fPoint(114.f, 0.f), 0, 0.1f, 17, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Death_L", m_pImg, fPoint(0.f, 0.f), fPoint(114.f, 131.f), fPoint(114.f, 0.f), 0, 0.1f, 17, false, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Attack_R", m_pImg, fPoint(0.f, 260.f), fPoint(202.f, 120.f), fPoint(202.f, 0.f), 5, 0.07f, 23, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Attack_L", m_pImg, fPoint(0.f, 260.f), fPoint(202.f, 120.f), fPoint(202.f, 0.f), 5, 0.07f, 23, false, true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"Acolyte_Walk_L");
	for (int i = 0; i < 15; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 40.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Acolyte_Idle_L");
	for (int i = 0; i < 13; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 40.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Acolyte_Attack_R");
	for (int i = 0; i < 23; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 158.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Acolyte_Attack_L");
	for (int i = 0; i < 23; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 202.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Acolyte_Hit_R");
	pAnim->GetFrame(0).fptOffset.x += 30.f;
	pAnim->GetFrame(2).fptOffset.x -= 10.f;
	pAnim->GetFrame(3).fptOffset.x -= 50.f;
	pAnim->GetFrame(4).fptOffset.x -= 60.f;
	pAnim->GetFrame(5).fptOffset.x -= 80.f;
	pAnim->GetFrame(6).fptOffset.x -= 70.f;
	pAnim->GetFrame(7).fptOffset.x -= 20.f;
	pAnim->GetFrame(10).fptOffset.x += 30.f;
	pAnim->GetFrame(11).fptOffset.x += 40.f;

	pAnim = GetAnimator()->FindAnimation(L"Acolyte_Hit_L");
	pAnim->GetFrame(0).fptOffset.x -= 70.f;
	pAnim->GetFrame(1).fptOffset.x -= 50.f;
	pAnim->GetFrame(2).fptOffset.x -= 40.f;
	pAnim->GetFrame(4).fptOffset.x += 10.f;
	pAnim->GetFrame(5).fptOffset.x += 40.f;
	pAnim->GetFrame(6).fptOffset.x += 40.f;
	pAnim->GetFrame(7).fptOffset.x -= 10.f;
	pAnim->GetFrame(8).fptOffset.x -= 40.f;
	pAnim->GetFrame(9).fptOffset.x -= 40.f;
	pAnim->GetFrame(10).fptOffset.x -= 70.f;
	pAnim->GetFrame(11).fptOffset.x -= 80.f;
}

void CEnemy_Acolyte::Attack()
{
	float iMoveStartTime = GetAnimator()->GetCurAnim()->GetFrame(0).fDuration * 6;

	if (GetAttCount() == 0)
	{
		m_fAtkAccTime += fDeltaTime;

		if (iMoveStartTime <= m_fAtkAccTime)
		{
			m_bIsAttacking = true;
		}
	}

	if (m_bIsAttacking)
	{
		SetVelocity(500.f);
		SetAttCount(1);
		m_bIsAttacking = false;
		m_fAtkAccTime = 0.f;
		GetEnemyInfo().pWeapon->Attack();
	}

	fVector2D fvPos = GetPos();
	float fVelocity = GetVelocity();

	float fFriction = GetDir().x * (-1) * 500.f * fDeltaTime;

	if (GetDir().x > 0.f)
	{
		if (fVelocity <= abs(fFriction))
		{
			fVelocity = 0.f;
		}
		else
		{
			fVelocity += fFriction;
		}
		SetVelocity(fVelocity);
	}
	else
	{
		if (fVelocity <= fFriction)
		{
			fVelocity = 0.f;
		}
		else
		{
			fVelocity -= fFriction;
		}
		SetVelocity(fVelocity);
	}

	fvPos.x += GetDir().x * fVelocity * fDeltaTime;
	SetPos(fvPos);
}

void CEnemy_Acolyte::Hit(CGameObject* other)
{
	CEnemy::Hit(other);

	GetAnimator()->FindAnimation(L"Acolyte_Hit_R")->SetFrame(0);
	GetAnimator()->FindAnimation(L"Acolyte_Hit_L")->SetFrame(0);
}

void CEnemy_Acolyte::OnCollision(CCollider* other)
{
	CEnemy::OnCollision(other);
}
