#include "framework.h"
#include "CPlayerSword.h"
#include "CCollider.h"
#include "CPlayer.h"

CPlayerSword::CPlayerSword()
{
	SetName(L"Sword_MeaCulpa");
	SetScale(fPoint(100.f, 50.f));
	SetAtk(50.f);
	m_fAttTime = 0.3f;

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	//CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON_FRONT, GROUP_GAMEOBJ::ENEMY);
	//CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON_BEHIND, GROUP_GAMEOBJ::ENEMY);
	// Test
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON_FRONT, GROUP_GAMEOBJ::BUILDING);
}

CPlayerSword::~CPlayerSword()
{
}

CPlayerSword* CPlayerSword::Clone()
{
	return new CPlayerSword(*this);
}

void CPlayerSword::update()
{
	
}

void CPlayerSword::render()
{
	component_render();
}

void CPlayerSword::Attack()
{
	CGameObject* ownerObj = GetOwnerObj();
	if (ownerObj == nullptr) return;

	CPlayer* user = dynamic_cast<CPlayer*>(ownerObj);

	if (nullptr != user)
	{
		SetPos(user->GetPos());
		if (user->GetDirVector().x > 0.f)
		{
			GetCollider()->SetFinalPos(GetPos());
			GetCollider()->SetOffsetPos(fPoint(100.f, 0.f));
		}
		else
		{
			GetCollider()->SetFinalPos(GetPos());
			GetCollider()->SetOffsetPos(fPoint(-35.f, 0.f));
		}
	}
}

void CWeapon::OnCollision(CCollider* other)
{
	// TODO : 적에게 맞았다면 바로 없애주도록 설정
	if (L"PrayerTable" == other->GetOwnerObj()->GetName())
	{
		static float fTime = 0.f;
		fTime += fDeltaTime;

		if (fTime > 0.25f)
		{
			SetPos(fPoint(-10000.f, -10000.f));
			GetCollider()->SetFinalPos(GetPos());
			fTime = 0.f;
		}
	}
}
