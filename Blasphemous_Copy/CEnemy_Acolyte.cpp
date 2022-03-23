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

	tEnemyInfo info = {};
	info.fHP = 150.f;
	info.fAtt = 20.f;
	info.fAttRange = 300.f;
	info.fAttDelayTime = 2.f;
	info.fRecogRange = 400.f;
	info.fVelocity = 100.f;
	info.fInvTime = 0.5f;
	info.iMoney = 20;

	info.pWeapon = new CSpear;
	info.pWeapon->SetOwnerObj(this);
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	pCurScene->AddObject(info.pWeapon, GROUP_GAMEOBJ::WEAPON);
	SetEnemyInfo(info);

	CreateCollider();
	GetCollider()->SetScale(fPoint(30.f, 100.f));
	GetCollider()->SetOffsetPos(fPoint(-20.f, 65.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Acolyte_Idle_R", m_pImg, fPoint(0.f, 133.f), fPoint(41.f, 122.f), fPoint(42.f, 0.f), 0, 0.05f, 13, true, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Idle_L", m_pImg, fPoint(0.f, 133.f), fPoint(41.f, 122.f), fPoint(42.f, 0.f), 0, 0.05f, 13, true, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Walk_R", m_pImg, fPoint(560.f, 131.f), fPoint(45.f, 129.f), fPoint(45.f, 0.f), 0, 0.05f, 15, true, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Walk_L", m_pImg, fPoint(560.f, 131.f), fPoint(45.f, 129.f), fPoint(45.f, 0.f), 0, 0.05f, 15, true, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Hit_R", m_pImg, fPoint(1010.f, 260.f), fPoint(83.f, 117.f), fPoint(83.f, 0.f), 0, 0.05f, 12, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Hit_L", m_pImg, fPoint(1010.f, 260.f), fPoint(83.f, 117.f), fPoint(83.f, 0.f), 0, 0.05f, 12, false, true);
	GetAnimator()->CreateAnimation(L"Acolyte_ParryReact_R", m_pImg, fPoint(1008.f, 377.f), fPoint(168.f, 111.f), fPoint(168.f, 0.f), 0, 0.05f, 5, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_ParryReact_L", m_pImg, fPoint(1008.f, 377.f), fPoint(168.f, 111.f), fPoint(168.f, 0.f), 0, 0.05f, 5, false, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Death_R", m_pImg, fPoint(0.f, 0.f), fPoint(114.f, 131.f), fPoint(114.f, 0.f), 0, 0.05f, 17, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Death_L", m_pImg, fPoint(0.f, 0.f), fPoint(114.f, 131.f), fPoint(114.f, 0.f), 0, 0.05f, 17, false, true);
	GetAnimator()->CreateAnimation(L"Acolyte_Attack_R", m_pImg, fPoint(0.f, 260.f), fPoint(202.f, 120.f), fPoint(202.f, 0.f), 5, 0.05f, 23, false, false);
	GetAnimator()->CreateAnimation(L"Acolyte_Attack_L", m_pImg, fPoint(0.f, 260.f), fPoint(202.f, 120.f), fPoint(202.f, 0.f), 5, 0.05f, 23, false, true);

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

	GetAnimator()->Play(L"Acolyte_Idle_R");
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

	default:
		break;
	}
}

void CEnemy_Acolyte::Attack()
{
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

	GetEnemyInfo().pWeapon->Attack();
}

void CEnemy_Acolyte::OnCollision(CCollider* other)
{
	CEnemy::OnCollision(other);
}
