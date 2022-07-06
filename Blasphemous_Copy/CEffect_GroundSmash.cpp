#include "framework.h"
#include "CEffect_GroundSmash.h"
#include "CEffect_WoodThorn.h"
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

void CEffect_GroundSmash::SpawnThorns(int thornCount)
{
	for (int i = 1; i <= thornCount; ++i)
	{
		CEffect_WoodThorn* thornFx = new CEffect_WoodThorn();
		thornFx->SetOwnerObj(GetOwnerObj());

		if (GetPos().x > GetOwnerObj()->GetPos().x)
		{
			thornFx->SetPos(fPoint(GetPos().x + (i * thornFx->GetScale().x + 20.f), GetPos().y));
		}
		else
		{
			thornFx->SetPos(fPoint(GetPos().x - (i * thornFx->GetScale().x + 20.f), GetPos().y));
		}

		CreateObj(thornFx, GROUP_GAMEOBJ::ENEMY_ATT_FX);
	}
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
