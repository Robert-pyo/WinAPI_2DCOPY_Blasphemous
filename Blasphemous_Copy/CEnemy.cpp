#include "framework.h"
#include "CEnemy.h"
#include "CCollider.h"
#include "AI.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CTile.h"

CEnemy::CEnemy()
{
	m_bIsGrounded = false;
	m_fAccelGravity = 0.f;
	m_pAI = nullptr;
	m_tEnmInfo = {};
	m_fvCurDir = {};
	m_fvPrevDir = {GetPos().x, GetPos().y};

	m_tEnmInfo.fHP = 0.f;
	m_tEnmInfo.fAtt = 0.f;
	m_tEnmInfo.fAttRange = 0.f;
	m_tEnmInfo.fAttDelayTime = 0.f;
	m_tEnmInfo.fRecogRange = 0.f;
	m_tEnmInfo.fVelocity = 0.f;
	m_tEnmInfo.fInvTime = 0.f;
	m_tEnmInfo.iMoney = 0.f;

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::FLOOR);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::TILE);
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
		13, RGB(0, 255, 0));

	WCHAR hp[5];
	swprintf_s(hp, L"%4d", (int)m_tEnmInfo.fHP);
	wstring strHp = L"HP : ";
	strHp += hp;
	CRenderManager::GetInst()->RenderText(strHp,
		fptRenderPos.x - GetScale().x,
		fptRenderPos.y + GetScale().y / 2.f,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y,
		14, RGB(0, 255, 0));
}

void CEnemy::SetImage(const wstring& strKey, const wstring& strPath)
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strPath);
}

CD2DImage* CEnemy::GetImage()
{
	return m_pImg;
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
	CPlayer* player = (CPlayer*)pPlayer;
	m_tEnmInfo.fHP -= player->GetPlayerAbility().fAtt;

	if (GetAI()->GetCurState()->GetState() == ENEMY_STATE::DEAD) return;

	if (m_tEnmInfo.fHP <= 0.f)
	{
		Die();
		return;
	}

	if (GetAI()->GetCurState()->GetState() == ENEMY_STATE::ATTACK) return;
	if (GetAI()->GetCurState()->GetState() == ENEMY_STATE::HIT) return;
	// 맞았으면 HIT 상태로 전환
	ChangeAIState(m_pAI, ENEMY_STATE::HIT);
}

void CEnemy::Die()
{
	ChangeAIState(m_pAI, ENEMY_STATE::DEAD);
}

void CEnemy::OnCollision(CCollider* target)
{
	if (GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup() ||
		GROUP_GAMEOBJ::TILE == target->GetOwnerObj()->GetObjGroup())
	{
		fVector2D fvDiff = CCollisionManager::GetInst()->GetColliderDiff(GetCollider(), target);

		CTile* pTile = (CTile*)target->GetOwnerObj();

		// 플레이어 바닥 및 벽 충돌 처리

		// 왼쪽 벽
		if (m_fvCurDir.x < 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				// 플레이어가 벽보다 오른쪽에 있을 때
				if (fvDiff.y > fvDiff.x && GetCollider()->GetBorderPos().right > target->GetBorderPos().right)
				{
					fPoint fptPos = GetPos();
					fptPos.x += m_tEnmInfo.fVelocity * fDeltaTime;
					m_tEnmInfo.fVelocity = 0.f;
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
				// 플레이어가 벽보다 왼쪽에 있을 때
				if (fvDiff.y > fvDiff.x && GetCollider()->GetBorderPos().left < target->GetBorderPos().left)
				{
					fPoint fptPos = GetPos();
					fptPos.x -= m_tEnmInfo.fVelocity * fDeltaTime;
					m_tEnmInfo.fVelocity = 0.f;
					SetPos(fptPos);
				}
			}
		}

		if (m_fAccelGravity > 0.f || pTile->GetGroup() == GROUP_TILE::GROUND)
		{
			// 아래쪽
			if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
			{
				if (fvDiff.y < fvDiff.x)
				{
					fPoint fptPos = GetPos();
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					fptPos.y -= fvDiff.y;
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
	if (GROUP_GAMEOBJ::TILE == target->GetOwnerObj()->GetObjGroup())
	{
		CTile* pTile = (CTile*)target->GetOwnerObj();
		if (pTile->GetGroup() == GROUP_TILE::WALL)
		{
			SetDir(GetDir() * (-1));
		}
	}
}
