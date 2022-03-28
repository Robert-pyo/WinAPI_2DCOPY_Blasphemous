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
			if (m_arrCheckGroup[row] & (1 << col))	// row��° �׷��� -> col��° �׷�� �浹 �����ϸ�
			{
				CollisionGroupUpdate((GROUP_GAMEOBJ)row, (GROUP_GAMEOBJ)col);
			}
		}
	}
}

void CCollisionManager::CollisionGroupUpdate(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	// ���� ��
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	
	const vector<CGameObject*>& vecLeft = pCurScene->GetObjGroup(objLeft);
	const vector<CGameObject*>& vecRight = pCurScene->GetObjGroup(objRight);

	for (int i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� �� -> �� ������Ʈ ����
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (int j = 0; j < vecRight.size(); ++j)
		{
			// �浹ü ���� �� ����
			if (nullptr == vecRight[j]->GetCollider())
				continue;
			// �ڱ� �ڽ� ������Ʈ�̸� ����
			if (vecLeft[i] == vecRight[j])
				continue;

			// �浹ü ���� ID �ҷ��ͼ� KEY�� ����
			COLLISION_ID collision_ID;
			collision_ID.leftID = vecLeft[i]->GetCollider()->GetID();
			collision_ID.rightID = vecRight[j]->GetCollider()->GetID();

			// ������ ���� key������ �浹 ������ �ִ��� ã��
			map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(collision_ID.colID);

			// ã�Ҵµ� ���� �浹 ������ ���ٸ� -> ó�� �浹�ϴ� �Ŷ��
			if (m_mapCollisionInfo.end() == iter)
			{
				// �浹 ������ ID�� �浹���� ���ٴ� ������ �־���
				m_mapCollisionInfo.insert(make_pair(collision_ID.colID, false));
				// �ݺ��ڰ� �־��� key�� ����Ű�� �ְԲ� ��
				iter = m_mapCollisionInfo.find(collision_ID.colID);
			}

			// ã�Ҵµ� ���� �浹 ������ �ִٸ� -> �浹 �˻�
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// prev O, cur O
				if (iter->second)
				{
					// �浹ü �� �ϳ��� disable ���¶�� �浹 ����
					if (vecLeft[i]->IsDisabled() || vecRight[j]->IsDisabled())
					{
						vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
						iter->second = false;
					}
					else
					{
						// �浹 ��
						vecLeft[i]->GetCollider()->OnCollision(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollision(vecLeft[i]->GetCollider());
						iter->second = true;
					}
				}
				// prev X, cur O
				else
				{
					// �浹ü �� �ϳ��� disable ���¶�� �浹 X
					if (!(vecLeft[i]->IsDisabled() || vecRight[j]->IsDisabled()))
					{
						// �浹 ����
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
					// �浹 ����
					vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
				}
				// prev X, cur X
				// �浹 ���� ����
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

	// ���� �浹ü ���� x�Ÿ�(�������� x �Ÿ�)���� �浹ü�� �������� ���� ���̰� �� ũ�ٸ� -> �浹��
	// y���� ����
	if (abs(fptLeftPos.x - fptRightPos.x) < (fptLeftScale.x + fptRightScale.x) / 2.f
		&& abs(fptLeftPos.y - fptRightPos.y) < (fptLeftScale.y + fptRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionManager::CheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	UINT iRow;	// ��
	UINT iCol;	// ��

	// �� ���� ��(eGroup_GameObj�� �׷� ������ ���� ��)�� ������ ��
	// ex) 5��° �׷��� 1��° �׷�� �浹 vs 1��° �׷�� 5��° �׷��� �浹 <- ���� �Ȱ���
	// �׷��Ƿ� �� �׷��� �浹�Ǵ��� Ȯ���� �� ���� �� �׷쿡���� Ȯ���� �� �ֵ��� ��
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

	// ???? ???? ???? ?0?? | 0000 0000 0000 0100 == ???? ???? ???? ?1?? -> 1�� ����� üũ
	m_arrCheckGroup[iRow] |= (1 << iCol);
}

void CCollisionManager::UnCheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	UINT iRow;	// ��
	UINT iCol;	// ��

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

	// ???? ???? ???? ?1?? & 1111 1111 1111 1011 == ???? ???? ???? ?0?? -> üũ ����
	m_arrCheckGroup[iRow] &= ~(1 << iCol);
}

void CCollisionManager::Reset()
{
	// ������(sizeof(UINT) * (UINT)eGroup_GameObj::Size)��ŭ 0���� m_arrCheckGroup�� �ʱ�ȭ
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
