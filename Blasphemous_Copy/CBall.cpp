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
	// 볼의 충돌 감지부분이 볼과 같이 움직일 수 있도록 업데이트마다 갱신
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

// 충돌했는지 검사하여 충돌했다면 Ball이 정반사되도록 한다
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
//	// 새로운 볼 생성
//	CBall* newBall = new CBall;
//	// 생성된 볼이 타겟팅할 오브젝트를 설정
//	for (int i = 0; i < collisionTarget.size(); ++i)
//	{
//		newBall->SetCollisionTarget(collisionTarget[i]);
//	}
//
//	// 현재 씬 받아와서 오브젝트 넣어주기
//	CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();
//	pCurScene->AddObject(newBall, eGroup_GameObj::Default);
//
//	// 새로 생성된 볼 관리할 벡터에 넣어주기
//	generatedBall.push_back(newBall);
//}
