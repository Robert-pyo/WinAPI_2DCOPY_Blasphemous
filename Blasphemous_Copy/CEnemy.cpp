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

		// �÷��̾� �ٴ� �� �� �浹 ó��

		// ���� ��
		if (m_fvCurDir.x < 0.f)
		{
			// y�� ��ġ�� ���� �ʴ� ��� ����
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				// �÷��̾ ������ �����ʿ� ���� ��
				if (yDiff > xDiff && GetCollider()->GetBorderPos().right > target->GetBorderPos().right)
				{
					fPoint fptPos = GetPos();
					fptPos.x += (float)(target->GetBorderPos().right - GetCollider()->GetBorderPos().left);
					SetPos(fptPos);
				}
			}
		}
		// ������ ��
		if (m_fvCurDir.x > 0.f)
		{
			// y�� ��ġ�� ���� �ʴ� ��� ����
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				// �÷��̾ ������ ���ʿ� ���� ��
				if (yDiff > xDiff && GetCollider()->GetBorderPos().left < target->GetBorderPos().left
					&& GetCollider()->GetBorderPos().right > target->GetBorderPos().left)
				{
					fPoint fptPos = GetPos();
					fptPos.x -= (float)(GetCollider()->GetBorderPos().right - target->GetBorderPos().left);
					SetPos(fptPos);
				}
			}
		}

		// ���� / �Ʒ��� ��
		if (m_fAccelGravity > 0.f)
		{
			// ����
			if (GetCollider()->GetBorderPos().bottom > target->GetBorderPos().bottom &&
				GetCollider()->GetBorderPos().top <= target->GetBorderPos().bottom)
			{
				yDiff = (target->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					// �浹�� ������ ���鿡�� �հ� �� ������ ����Ͽ� ���� ��ġ�� ������
					fptPos.y += (float)(target->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);
					SetPos(fptPos);
				}

			}
			// �Ʒ���
			if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					// �浹�� ������ ���鿡�� �հ� �� ������ ����Ͽ� ���� ��ġ�� ������
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
