#include "framework.h"
#include "CEffect_GroundSmash.h"
#include "CCollider.h"

CEffect_GroundSmash::CEffect_GroundSmash()
{
	SetName(L"FxBossGroundSmash");
	SetDuration(1.0f);
	SetScale(fPoint(150.f, 50.f));

	m_fFxAccTime = 0.f;

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY_ATT_FX, GROUP_GAMEOBJ::PLAYER);
}

CEffect_GroundSmash::~CEffect_GroundSmash()
{
}

CEffect_GroundSmash* CEffect_GroundSmash::Clone()
{
	return new CEffect_GroundSmash(*this);
}

void CEffect_GroundSmash::update()
{
	m_fFxAccTime += fDeltaTime;

	if (m_fFxAccTime > GetDuration())
	{
		DeleteObj(this);
	}
}

void CEffect_GroundSmash::render()
{
	component_render();
}

void CEffect_GroundSmash::OnCollisionEnter(CCollider* other)
{
	if (other->GetOwnerObj()->GetName() == L"Player")
	{
		if (!CPlayer::GetPlayer()->IsInvincible())
		{
			CPlayer::GetPlayer()->Hit(GetOwnerObj());
			DeleteObj(this);
		}
	}
}
