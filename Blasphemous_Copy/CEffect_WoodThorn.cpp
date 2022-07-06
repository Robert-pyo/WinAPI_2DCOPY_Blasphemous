#include "framework.h"
#include "CEffect_WoodThorn.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEffect_WoodThorn::CEffect_WoodThorn()
{
	SetName(L"FxPiedadThorn");
	SetScale(fPoint(64.f, 128.f));
	LoadEffectImg(L"FxPiedadThorn", L"texture\\Enemy\\Piedad\\GroundSmash\\Thorn\\thorns_tower_anim.png");

	m_fFxAccTime = 0.f;
	m_fSpikeSpeed = 500.f;
	m_bIsSpikeDone = false;

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	GetCollider()->SetOffsetPos(fPoint(GetPos().x, GetPos().y + GetScale().y));
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY_ATT_FX, GROUP_GAMEOBJ::PLAYER);

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"SpawnThorn", GetFxImg(), fPoint(0.f, 0.f), fPoint(64.f, 128.f), fPoint(64.f, 0.f), 6, 0.05f, 42, false, false);

	GetAnimator()->Play(L"SpawnThorn");
	m_fDurationPerFrame = GetAnimator()->GetCurAnim()->GetFrame(0).fDuration;
	SetDuration(GetAnimator()->GetCurAnim()->GetAnimDuration());
}

CEffect_WoodThorn::~CEffect_WoodThorn()
{
}

CEffect_WoodThorn* CEffect_WoodThorn::Clone()
{
	return new CEffect_WoodThorn(*this);
}

void CEffect_WoodThorn::update()
{
	GetAnimator()->update();

	m_fFxAccTime += fDeltaTime;

	if (m_fFxAccTime > GetDuration())
	{
		DeleteObj(this);
	}

	if (m_fFxAccTime >= m_fDurationPerFrame * 22)
	{
		if (m_fFxAccTime >= m_fDurationPerFrame * 37)
		{
			if (GetCollider()->GetScale().x <= 0.1f) return;

			GetCollider()->SetScale(fPoint(0.f, 0.f));
		}

		// 소환된 위치보다 높이 올라가면 return
		if (GetCollider()->GetBorderPos().top <= GetPos().y - 100.f) return;

		GetCollider()->SetOffsetPos(fPoint(GetCollider()->GetOffsetPos().x, GetCollider()->GetOffsetPos().y - m_fSpikeSpeed * fDeltaTime));
	}
}

void CEffect_WoodThorn::render()
{
	component_render();
}

void CEffect_WoodThorn::OnCollisionEnter(CCollider* other)
{
	if (other->GetOwnerObj()->GetName() == L"Player")
	{
		if (!CPlayer::GetPlayer()->IsInvincible())
		{
			CPlayer::GetPlayer()->Hit(50.f);
		}
	}
}
