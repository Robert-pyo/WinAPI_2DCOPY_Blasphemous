#include "framework.h"
#include "CEnemy.h"
#include "CCollider.h"
#include "AI.h"

CEnemy::CEnemy()
{
	m_bIsGrounded = false;
	m_fVelocity = 0.f;
	m_fAccelGravity = 0.f;

	CreateCollider();
	GetCollider()->SetScale(fPoint(100.f, 100.f));
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
	if (nullptr != m_pAI)
	{
		m_pAI->update();
	}
}

void CEnemy::render()
{
	component_render();
}

void CEnemy::SetAI(AI* pAI)
{
	m_pAI = pAI;
	m_pAI->m_pOwner = this;
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
	if (GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup())
	{
		LONG yDiff = 0;
		LONG xDiff = 0;
		if (target->GetBorderPos().left > GetCollider()->GetBorderPos().left)
		{
			xDiff = (GetCollider()->GetBorderPos().right - target->GetBorderPos().left);
		}
		else if (target->GetBorderPos().right < GetCollider()->GetBorderPos().right)
		{
			xDiff = (target->GetBorderPos().right - GetCollider()->GetBorderPos().left);
		}
		else
			xDiff = (GetCollider()->GetBorderPos().right - GetCollider()->GetBorderPos().left);

		// 플레이어 바닥 및 벽 충돌 처리

		// 왼쪽 벽
		if (m_fvCurDir.x < 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 오른쪽에 있을 때
				if (yDiff > xDiff && GetCollider()->GetBorderPos().right > target->GetBorderPos().right)
				{
					fPoint fptPos = GetPos();
					fptPos.x += (float)(target->GetBorderPos().right - GetCollider()->GetBorderPos().left);
					SetPos(fptPos);
				}
			}
		}
		// 오른쪽 벽
		if (m_fvCurDir.x > 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 왼쪽에 있을 때
				if (yDiff > xDiff && GetCollider()->GetBorderPos().left < target->GetBorderPos().left
					&& GetCollider()->GetBorderPos().right > target->GetBorderPos().left)
				{
					fPoint fptPos = GetPos();
					fptPos.x -= (float)(GetCollider()->GetBorderPos().right - target->GetBorderPos().left);
					SetPos(fptPos);
				}
			}
		}

		// 위쪽 / 아래쪽 벽
		if (m_fAccelGravity > 0.f)
		{
			// 위쪽
			if (GetCollider()->GetBorderPos().bottom > target->GetBorderPos().bottom &&
				GetCollider()->GetBorderPos().top <= target->GetBorderPos().bottom)
			{
				yDiff = (target->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					fptPos.y += (float)(target->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);
					SetPos(fptPos);
				}

			}
			// 아래쪽
			if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					fptPos.y -= (float)(GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);
					SetPos(fptPos);

					m_bIsGrounded = true;

					m_fAccelGravity = 0.f;
				}
			}
		}
	}
}

void CEnemy::OnCollisionEnter(CCollider* target)
{
	
}
