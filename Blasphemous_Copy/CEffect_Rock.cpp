#include "framework.h"
#include "CEffect_Rock.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CEnemy.h"

CEffect_Rock::CEffect_Rock()
{
	SetName(L"FxThrownRock");
	SetScale(fPoint(32.f, 32.f));
	LoadEffectImg(L"FxThrownRock", L"texture\\Enemy\\Stoner\\stoner_rock_anim_merge.png");
	SetDuration(5.f);

	m_fSpeed = 300.f;
	m_fFxAccTime = 0.f;

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY_ATT_FX, GROUP_GAMEOBJ::PLAYER);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY_ATT_FX, GROUP_GAMEOBJ::TILE);

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ThrownRock", GetFxImg(), fPoint(64.f, 0.f), fPoint(16.f, 16.f), fPoint(0.f, 16.f), 0, 0.03f, 31, true, false);
	GetAnimator()->CreateAnimation(L"LandingRock", GetFxImg(), fPoint(0.f, 0.f), fPoint(63.f, 58.f), fPoint(0.f, 58.f), 0, 0.03f, 14, false, false);

	GetAnimator()->Play(L"ThrownRock");
}

CEffect_Rock::~CEffect_Rock()
{
}

CEffect_Rock* CEffect_Rock::Clone()
{
	return new CEffect_Rock(*this);
}

void CEffect_Rock::update()
{
	m_fFxAccTime += fDeltaTime;

	fVector2D pos = GetPos();
	pos.x += GetFxDir().x * m_fSpeed * fDeltaTime;
	pos.y += GetFxDir().y * m_fSpeed * fDeltaTime;
	SetPos(pos);

	if (GetDuration() <= m_fFxAccTime)
	{
		GetAnimator()->Play(L"LandingRock");

		DeleteObj(this);
	}

	if (GetAnimator()->GetCurAnim()->IsAnimDone())
	{
		DeleteObj(this);
	}

	GetAnimator()->update();
}

void CEffect_Rock::render()
{
	component_render();
}

void CEffect_Rock::init()
{
	fVector2D fvPlayerPos = CPlayer::GetPlayer()->GetPos();
	fVector2D fvEnemyPos = GetOwnerObj()->GetPos();

	fVector2D fvDir = fvPlayerPos - fvEnemyPos;
	fvDir.Normalize();
	SetFxDir(fvDir);
}

void CEffect_Rock::OnCollisionEnter(CCollider* other)
{
	if (other->GetOwnerObj()->GetObjGroup() == GROUP_GAMEOBJ::TILE ||
		other->GetOwnerObj()->GetName() == L"FXSwordSlash")
	{
		GetAnimator()->Play(L"LandingRock");

		m_fSpeed = 0.f;
	}

	if (other->GetOwnerObj()->GetName() == L"Player")
	{
		if (!CPlayer::GetPlayer()->IsInvincible())
		{
			GetAnimator()->Play(L"LandingRock");

			CPlayer::GetPlayer()->Hit(GetOwnerObj());

			m_fSpeed = 0.f;
		}
	}
}
