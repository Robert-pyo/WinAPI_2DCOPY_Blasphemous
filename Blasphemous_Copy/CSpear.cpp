#include "framework.h"
#include "CSpear.h"
#include "CCollider.h"

CSpear::CSpear()
{
	SetName(L"Spear");
	SetScale(fPoint(150.f, 50.f));
	SetAtt(20.f);
	SetAttDuration(1.15f);

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON_BEHIND, GROUP_GAMEOBJ::ENEMY);
}

CSpear::~CSpear()
{
}

CSpear* CSpear::Clone()
{
	return new CSpear(*this);
}

void CSpear::update()
{
}

void CSpear::render()
{
	component_render();
}

void CSpear::Attack()
{
	int a = 0;
}
