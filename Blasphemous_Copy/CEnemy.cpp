#include "framework.h"
#include "CEnemy.h"
#include "CCollider.h"
#include "CPlayer.h"

CEnemy::CEnemy()
{
	InitObject(fPoint(500, 100.f), fPoint(100.f, 100.f));
	m_strName	= L"Enemy_01";
	m_fVelocity = 500.0f;
	targetBall	= nullptr;
	timeCount	= 0;

	CreateCollider();
	GetCollider()->SetFinalPos(fPoint(m_fptPos.x, m_fptPos.y));
	GetCollider()->SetScale(fPoint(90.f, 90.f));
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
	MoveEnemyAI();
}

void CEnemy::render()
{
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);

	component_render();
}

void CEnemy::SetChaseTarget(CBall* target)
{
	this->targetBall = target;
}

void CEnemy::MoveEnemyAI()
{
}

void CEnemy::LinkTimeCount(UINT* timeCount)
{
	this->timeCount = timeCount;
}

void CEnemy::OnCollision(CCollider* target)
{
	
}

void CEnemy::OnCollisionEnter(CCollider* target)
{
	if (L"Player" == target->GetOwnerObj()->GetName())
	{
		CPlayer* playerObj = (CPlayer*)target->GetOwnerObj();

		if (playerObj->GetDirVector().x > 0)
		{
			if (playerObj->GetDirVector().y == 0)
				m_fptPos.x += 1;
		}
		else if (playerObj->GetDirVector().x < 0)
		{
			if (playerObj->GetDirVector().y == 0)
				m_fptPos.x -= 1;
		}
	}
}

void CEnemy::OnCollisionExit(CCollider* target)
{
}
