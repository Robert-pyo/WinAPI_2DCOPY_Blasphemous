#include "framework.h"
#include "CWeapon.h"

CWeapon::CWeapon()
{
	m_pOwner = nullptr;
	SetPos(fPoint(-10000.f, -10000.f));
	m_fAtk = 0.f;
}

CWeapon::~CWeapon()
{
}

void CWeapon::update()
{
}

void CWeapon::render()
{
}

CGameObject* CWeapon::GetOwnerObj()
{
	return m_pOwner;
}

const float CWeapon::GetAtkValue()
{
	return m_fAtk;
}

void CWeapon::SetOwnerObj(CGameObject* pOwner)
{
	m_pOwner = pOwner;
}

void CWeapon::SetAtk(const float atk)
{
	m_fAtk = atk;
}
