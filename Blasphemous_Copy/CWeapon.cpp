#include "framework.h"
#include "CWeapon.h"

CWeapon::CWeapon()
{
	m_pOwner = nullptr;
	SetPos(fPoint(-10000.f, -10000.f));
	m_fAtt = 0.f;
	m_fAttDuration = 0.f;
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

const float CWeapon::GetAttValue()
{
	return m_fAtt;
}

void CWeapon::SetOwnerObj(CGameObject* pOwner)
{
	m_pOwner = pOwner;
}

void CWeapon::SetAtt(const float att)
{
	m_fAtt = att;
}

const float CWeapon::GetDuration()
{
	return m_fAttDuration;
}

void CWeapon::SetAttDuration(const float duration)
{
	m_fAttDuration = duration;
}
