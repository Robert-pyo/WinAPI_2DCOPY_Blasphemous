#include "framework.h"
#include "CBall.h"
#include "CScene.h"

CBall::CBall()
{
	initObject(fPoint(WINSIZE_X / 2 - 100, WINSIZE_Y / 2), fPoint(30, 30));
	m_fVelocity		= INIT_VELOCITY;
	playerScored	= false;
	enemyScored		= false;
	m_fvMoveDir		= { 1, -1 };
}

CBall::~CBall()
{
}

void CBall::update()
{
	// ���� �浹 �����κ��� ���� ���� ������ �� �ֵ��� ������Ʈ���� ����
	this->SetRect(this->m_fptPos.x, this->m_fptPos.y, this->m_fptPos.x + this->m_fptScale.x, this->m_fptPos.y + this->m_fptScale.y);

	this->m_fptPos.x += (float)(this->m_fvMoveDir.x * this->m_fVelocity * fDeltaTime);
	this->m_fptPos.y += (float)(this->m_fvMoveDir.y * this->m_fVelocity * fDeltaTime);
}

void CBall::render(HDC hDC)
{
	//Rectangle(hDC, collisionTop.left, collisionTop.top, collisionTop.right, collisionTop.bottom);
	//Rectangle(hDC, collisionLeft.left, collisionLeft.top, collisionLeft.right, collisionLeft.bottom);
	//Rectangle(hDC, collisionRight.left, collisionRight.top, collisionRight.right, collisionRight.bottom);
	//Rectangle(hDC, collisionBottom.left, collisionBottom.top, collisionBottom.right, collisionBottom.bottom);
	Rectangle(hDC, (int)this->m_fptPos.x, (int)this->m_fptPos.y, (int)(this->m_fptPos.x + this->m_fptScale.x), (int)(this->m_fptPos.y + this->m_fptScale.y));
}

// �浹�ߴ��� �˻��Ͽ� �浹�ߴٸ� Ball�� ���ݻ�ǵ��� �Ѵ�
//void CBall::IsTouched(CRectangle* target)
//{
//	RECT* pIntersectRect = this->CheckBoxCollision(target);
//
//	if (this->collisionRight.right > WINSIZE_X)
//	{
//		this->pos.x = WINSIZE_X / 2;
//		this->pos.y = WINSIZE_Y / 2;
//
//		this->m_fVelocity = INIT_VELOCITY;
//		this->playerScored = true;
//	}
//	else if (this->collisionLeft.left < 0)
//	{
//		this->pos.x = WINSIZE_X / 2;
//		this->pos.y = WINSIZE_Y / 2;
//
//		this->m_fVelocity = INIT_VELOCITY;
//		this->enemyScored = true;
//	}
//	else if (this->collisionTop.top < 0)
//	{
//		this->pos.y += 1;
//		if (m_fvMoveDir.y < 0)
//			this->m_fvMoveDir.y *= -1;
//	}
//	else if (this->collisionBottom.bottom > WINSIZE_Y)
//	{
//		this->pos.y -= 1;
//		if (m_fvMoveDir.y > 0)
//			this->m_fvMoveDir.y *= -1;
//	}
//
//	if (pIntersectRect == nullptr) return;
//
//	if (pIntersectRect->left == target->collisionLeft.left)
//	{
//		this->pos.x -= 1;
//		this->m_fvMoveDir.x *= -1;
//	}
//
//	else if (pIntersectRect->right == target->collisionRight.right)
//	{
//		this->pos.x += 1;
//		this->m_fvMoveDir.x *= -1;
//	}
//
//	else if (pIntersectRect->top == target->collisionTop.top)
//	{
//		this->pos.y -= 1;
//		this->m_fvMoveDir.y *= -1;
//	}
//
//	else if (pIntersectRect->bottom == target->collisionBottom.bottom)
//	{
//		this->pos.y += 1;
//		this->m_fvMoveDir.y *= -1;
//	}
//}

void CBall::SetCollisionTarget(CRectangle* target)
{
	this->collisionTarget.push_back(target);
}

//void CBall::GenerateBall()
//{
//	// ���ο� �� ����
//	CBall* newBall = new CBall;
//	// ������ ���� Ÿ������ ������Ʈ�� ����
//	for (int i = 0; i < collisionTarget.size(); ++i)
//	{
//		newBall->SetCollisionTarget(collisionTarget[i]);
//	}
//
//	// ���� �� �޾ƿͼ� ������Ʈ �־��ֱ�
//	CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();
//	pCurScene->AddObject(newBall, eGroup_GameObj::Default);
//
//	// ���� ������ �� ������ ���Ϳ� �־��ֱ�
//	generatedBall.push_back(newBall);
//}
