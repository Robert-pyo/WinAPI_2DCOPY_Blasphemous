#include "framework.h"
#include "CSpear.h"
#include "CCollider.h"
#include "CEnemy.h"
#include "CEffect_Spear.h"

CSpear::CSpear()
{
	SetName(L"Spear");
	SetScale(fPoint(150.f, 50.f));
	SetAtt(20.f);
	SetAttDuration(1.15f);
	m_pFx = nullptr;
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
	CEnemy* ownerObj = (CEnemy*)GetOwnerObj();
	if (nullptr == ownerObj) return;

	SetPos(ownerObj->GetPos());
}

void CSpear::render()
{
	component_render();
}

void CSpear::Attack()
{
	m_pFx = new CEffect_Spear;
	m_pFx->SetOwnerObj(this);
	CreateObj(m_pFx, GROUP_GAMEOBJ::ENEMY_ATT_FX);

	m_pFx->SetFxStart(true);

	CEnemy* ownerObj = (CEnemy*)GetOwnerObj();
	if (nullptr == ownerObj) return;

	m_pFx->SetFxDir(ownerObj->GetDir());

	if (ownerObj->GetDir().x > 0.f)
	{
		m_pFx->GetCollider()->SetOffsetPos(fPoint(180.f, 60.f));
	}

	else
	{
		m_pFx->GetCollider()->SetOffsetPos(fPoint(-200.f, 60.f));
	}
}
