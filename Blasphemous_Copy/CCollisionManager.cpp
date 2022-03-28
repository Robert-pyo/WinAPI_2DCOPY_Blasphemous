#include "framework.h"
#include "CCollisionManager.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
{
	m_arrCheckGroup[0] = 0;
	m_fvDiff = {};
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::init()
{
}

void CCollisionManager::update()
{
	for (int row = 0; row < (UINT)GROUP_GAMEOBJ::SIZE; ++row)
	{
		for (int col = row; col < (UINT)GROUP_GAMEOBJ::SIZE; ++col)
		{
			if (m_arrCheckGroup[row] & (1 << col))	// row번째 그룹이 -> col번째 그룹과 충돌 가능하면
			{
				CollisionGroupUpdate((GROUP_GAMEOBJ)row, (GROUP_GAMEOBJ)col);
			}
		}
	}
}

void CCollisionManager::CollisionGroupUpdate(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	// 현재 씬
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	
	const vector<CGameObject*>& vecLeft = pCurScene->GetObjGroup(objLeft);
	const vector<CGameObject*>& vecRight = pCurScene->GetObjGroup(objRight);

	for (int i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없을 시 -> 그 오브젝트 무시
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (int j = 0; j < vecRight.size(); ++j)
		{
			// 충돌체 없을 시 무시
			if (nullptr == vecRight[j]->GetCollider())
				continue;
			// 자기 자신 오브젝트이면 무시
			if (vecLeft[i] == vecRight[j])
				continue;

			// 충돌체 고유 ID 불러와서 KEY값 생성
			COLLISION_ID collision_ID;
			collision_ID.leftID = vecLeft[i]->GetCollider()->GetID();
			collision_ID.rightID = vecRight[j]->GetCollider()->GetID();

			// 생성한 고유 key값으로 충돌 정보에 있는지 찾음
			map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(collision_ID.colID);

			// 찾았는데 이전 충돌 정보가 없다면 -> 처음 충돌하는 거라면
			if (m_mapCollisionInfo.end() == iter)
			{
				// 충돌 정보에 ID와 충돌한적 없다는 정보를 넣어줌
				m_mapCollisionInfo.insert(make_pair(collision_ID.colID, false));
				// 반복자가 넣어준 key를 가리키고 있게끔 함
				iter = m_mapCollisionInfo.find(collision_ID.colID);
			}

			// 찾았는데 이전 충돌 정보가 있다면 -> 충돌 검사
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// prev O, cur O
				if (iter->second)
				{
					// 충돌체 중 하나가 disable 상태라면 충돌 해제
					if (vecLeft[i]->IsDisabled() || vecRight[j]->IsDisabled())
					{
						vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
						iter->second = false;
					}
					else
					{
						// 충돌 중
						vecLeft[i]->GetCollider()->OnCollision(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollision(vecLeft[i]->GetCollider());
						iter->second = true;
					}
				}
				// prev X, cur O
				else
				{
					// 충돌체 중 하나가 disable 상태라면 충돌 X
					if (!(vecLeft[i]->IsDisabled() || vecRight[j]->IsDisabled()))
					{
						// 충돌 진입
						vecLeft[i]->GetCollider()->OnCollisionEnter(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollisionEnter(vecLeft[i]->GetCollider());
						iter->second = true;
					}
				}
			}
			else
			{
				// prev O, cur X
				if (iter->second)
				{
					// 충돌 해제
					vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
				}
				// prev X, cur X
				// 충돌 한적 없음
				iter->second = false;
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	// Box Collision
	fPoint fptLeftPos = pLeftCollider->GetFinalPos();
	fPoint fptRightPos = pRightCollider->GetFinalPos();

	fPoint fptLeftScale = pLeftCollider->GetScale();
	fPoint fptRightScale = pRightCollider->GetScale();

	// 만약 충돌체 간의 x거리(중점간의 x 거리)보다 충돌체의 반지름을 더한 길이가 더 크다면 -> 충돌함
	// y또한 동일
	if (abs(fptLeftPos.x - fptRightPos.x) < (fptLeftScale.x + fptRightScale.x) / 2.f
		&& abs(fptLeftPos.y - fptRightPos.y) < (fptLeftScale.y + fptRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionManager::CheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	UINT iRow;	// 행
	UINT iCol;	// 렬

	// 더 작은 수(eGroup_GameObj의 그룹 순서상 작은 수)를 행으로 둠
	// ex) 5번째 그룹이 1번째 그룹과 충돌 vs 1번째 그룹과 5번째 그룹이 충돌 <- 둘이 똑같음
	// 그러므로 두 그룹이 충돌되는지 확인할 때 작은 쪽 그룹에서만 확인할 수 있도록 함
	if ((UINT)objLeft > (UINT)objRight)
	{
		iRow = (UINT)objRight;
		iCol = (UINT)objLeft;
	}
	else
	{
		iRow = (UINT)objLeft;
		iCol = (UINT)objRight;
	}

	// ???? ???? ???? ?0?? | 0000 0000 0000 0100 == ???? ???? ???? ?1?? -> 1로 만들어 체크
	m_arrCheckGroup[iRow] |= (1 << iCol);
}

void CCollisionManager::UnCheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	UINT iRow;	// 행
	UINT iCol;	// 렬

	if ((UINT)objLeft > (UINT)objRight)
	{
		iRow = (UINT)objRight;
		iCol = (UINT)objLeft;
	}
	else
	{
		iRow = (UINT)objLeft;
		iCol = (UINT)objRight;
	}

	// ???? ???? ???? ?1?? & 1111 1111 1111 1011 == ???? ???? ???? ?0?? -> 체크 해제
	m_arrCheckGroup[iRow] &= ~(1 << iCol);
}

void CCollisionManager::Reset()
{
	// 사이즈(sizeof(UINT) * (UINT)eGroup_GameObj::Size)만큼 0으로 m_arrCheckGroup을 초기화
	memset(m_arrCheckGroup, 0, sizeof(UINT) * (UINT)GROUP_GAMEOBJ::SIZE);
}

const fVector2D& CCollisionManager::GetColliderDiff(CCollider* objLeft, CCollider* objRight)
{
	if (objRight->GetBorderPos().left > objLeft->GetBorderPos().left)
	{
		m_fvDiff.x = (objLeft->GetBorderPos().right - objRight->GetBorderPos().left);
	}
	else if (objRight->GetBorderPos().right < objLeft->GetBorderPos().right)
	{
		m_fvDiff.x = (objRight->GetBorderPos().right - objLeft->GetBorderPos().left);
	}
	else
		m_fvDiff.x = (objLeft->GetBorderPos().right - objLeft->GetBorderPos().left);

	m_fvDiff.y = objLeft->GetBorderPos().bottom - objRight->GetBorderPos().top;

	return m_fvDiff;
}
