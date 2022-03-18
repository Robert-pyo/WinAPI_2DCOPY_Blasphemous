#include "framework.h"
#include "CEnemy.h"
#include "CCollider.h"
#include "AI.h"
#include "CScene.h"
#include "CPlayer.h"

CEnemy::CEnemy()
{
	m_bIsGrounded = false;
	m_fAccelGravity = 0.f;
	m_pAI = nullptr;
	m_tEnmInfo = {};

	CreateCollider();
	GetCollider()->SetScale(fPoint(100.f, 100.f));
}

CEnemy::~CEnemy()
{
	if (nullptr != m_pAI)
		delete m_pAI;
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

	fPoint fptPos = GetPos();

	fptPos.y += m_fAccelGravity * fDeltaTime;

	SetPos(fptPos);

	m_fAccelGravity += GRAVITY * fDeltaTime;
	if (m_fAccelGravity >= 1000.f)
		m_fAccelGravity = 1000.f;
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

void CEnemy::Hit(CGameObject* pPlayer)
{
	CPlayer* player = (CPlayer*)pPlayer;
	m_tEnmInfo.fHP -= player->GetPlayerAbility().fAtt;

	// �¾����� HIT ���·� ��ȯ
	// ChangeAIState(m_pAI, ENEMY_STATE::HIT);
	if (m_tEnmInfo.fHP <= 0.f)
	{
		//Die();
	}
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

		if (m_fAccelGravity > 0.f)
		{
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
