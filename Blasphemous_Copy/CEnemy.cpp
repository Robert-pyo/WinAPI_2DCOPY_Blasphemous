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
	m_fvCurDir = {};
	m_fvPrevDir = {GetPos().x, GetPos().y};
}

CEnemy::~CEnemy()
{
	if (nullptr != m_pAI)
		delete m_pAI;
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

	m_fvPrevDir = m_fvCurDir;
}

void CEnemy::render()
{
	component_render();
}

void CEnemy::component_render()
{
	CGameObject::component_render();

	if (CSceneManager::GetInst()->GetIsDebugging())
	{
		debug_render();
	}
}

void CEnemy::debug_render()
{
	CGameObject::debug_render();

	wstring curState = L"";

	switch (m_pAI->GetCurState()->GetState())
	{
	case ENEMY_STATE::IDLE:
		curState = L"Idle";
		break;
	case ENEMY_STATE::PATROL:
		curState = L"Patrol";
		break;
	case ENEMY_STATE::TRACE:
		curState = L"Trace";
		break;
	case ENEMY_STATE::ATTACK:
		curState = L"Attack";
		break;
	case ENEMY_STATE::RUN:
		curState = L"Run";
		break;
	case ENEMY_STATE::HIT:
		curState = L"Hit";
		break;
	case ENEMY_STATE::DEAD:
		curState = L"Dead";
		break;
	default:
		curState = L"None";
		break;
	}

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(GetCollider()->GetFinalPos());

	CRenderManager::GetInst()->RenderText(curState,
		fptRenderPos.x - GetScale().x * 2.f,
		fptRenderPos.y - GetScale().y / 1.5f,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y,
		15, RGB(0, 255, 0));
}

AI* CEnemy::GetAI()
{
	return m_pAI;
}

void CEnemy::SetAI(AI* pAI)
{
	m_pAI = pAI;
	m_pAI->m_pOwner = this;
}

void CEnemy::Hit(CGameObject* pPlayer)
{
	if (m_tEnmInfo.bIsInvincible) return;

	CPlayer* player = (CPlayer*)pPlayer;
	m_tEnmInfo.fHP -= player->GetPlayerAbility().fAtt;

	// 맞았으면 HIT 상태로 전환
	ChangeAIState(m_pAI, ENEMY_STATE::HIT);

	if (m_tEnmInfo.fHP <= 0.f)
	{
		Die();
	}
}

void CEnemy::Die()
{
	DeleteObj(this);
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

		if (m_fAccelGravity > 0.f)
		{
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
