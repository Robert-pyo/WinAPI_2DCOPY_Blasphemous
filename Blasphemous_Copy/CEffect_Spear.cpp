#include "framework.h"
#include "CEffect_Spear.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CWeapon.h"

CEffect_Spear::CEffect_Spear()
{
	SetName(L"FxEnemySpear");
	SetDuration(1.0f);
	SetScale(fPoint(300.f, 60.f));

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY_ATT_FX, GROUP_GAMEOBJ::PLAYER);
}

CEffect_Spear::~CEffect_Spear()
{
}

CEffect_Spear* CEffect_Spear::Clone()
{
	return new CEffect_Spear(*this);
}

void CEffect_Spear::update()
{
	SetPos(GetOwnerObj()->GetPos());

	static float fxAccTime = 0.f;
	if (IsFxStart())
	{
		fxAccTime += fDeltaTime;
	}
	if (GetDuration() <= fxAccTime)
	{
		fxAccTime = 0.f;
		DeleteObj(this);
	}
}

void CEffect_Spear::render()
{
	component_render();
}

void CEffect_Spear::OnCollisionEnter(CCollider* other)
{
	if (L"Player" == other->GetOwnerObj()->GetName())
	{
		CWeapon* pWeapon = (CWeapon*)GetOwnerObj();
		CGameObject* pEnemy = pWeapon->GetOwnerObj();

		if (!CPlayer::GetPlayer()->IsInvincible())
		{
			CPlayer::GetPlayer()->Hit(pEnemy);
		}
	}
}
