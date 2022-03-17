#include "framework.h"
#include "CSword.h"
#include "CCollider.h"
#include "CPlayer.h"

CSword::CSword()
{
	SetName(L"Sword_MeaCulpa");
	m_pOwner = nullptr;
	SetPos(fPoint(-100.f, -100.f));
	SetScale(fPoint(25.f, 50.f));

	CreateCollider();
	GetCollider()->SetScale(GetScale());
}

CSword::~CSword()
{
}

CSword* CSword::Clone()
{
	return new CSword(*this);
}

void CSword::update()
{
}

void CSword::render()
{
	component_render();
}

void CSword::SetOwner(CGameObject* pOwner)
{
	m_pOwner = pOwner;
}

void CSword::Attack()
{
	CPlayer* user = dynamic_cast<CPlayer*>(m_pOwner);

	if (nullptr != user)
	{
		SetPos(user->GetPos());
		if (user->GetDirVector().x > 0.f)
		{
			GetCollider()->SetOffsetPos(fPoint(GetPos().x + 10.f, GetPos().y));
		}
		else
		{
			GetCollider()->SetOffsetPos(fPoint(GetPos().x - 10.f, GetPos().y));
		}
	}
}
