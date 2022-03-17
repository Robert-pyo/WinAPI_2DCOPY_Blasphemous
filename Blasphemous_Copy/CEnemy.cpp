#include "framework.h"
#include "CEnemy.h"
#include "CCollider.h"
#include "CPlayer.h"

CEnemy::CEnemy()
{
	InitObject(fPoint(500, 100.f), fPoint(100.f, 100.f));
	SetName(L"Enemy_01");
	m_fVelocity = 500.0f;
}

CEnemy::~CEnemy()
{
}

CEnemy* CEnemy::Clone()
{
	return new CEnemy(*this);
}

void CEnemy::update()
{
	
}

void CEnemy::render()
{
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());

	component_render();
}

void CEnemy::SetVelocity(float fVelocity)
{
	m_fVelocity = fVelocity;
}

float CEnemy::GetVelocity()
{
	return m_fVelocity;
}

void CEnemy::OnCollision(CCollider* target)
{
	
}

void CEnemy::OnCollisionEnter(CCollider* target)
{
	
}

void CEnemy::OnCollisionExit(CCollider* target)
{
}
