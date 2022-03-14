#pragma once
#include "CRectangle.h"
#include "CBall.h"

class CEnemy : public CGameObject
{
private:
	float	m_fVelocity;
	CBall*	targetBall;
	UINT*	timeCount;

public:
	CEnemy();
	virtual ~CEnemy();
	virtual CEnemy* Clone();

	virtual void update() final;
	virtual void render() final;

	void SetChaseTarget(CBall* target);
	void MoveEnemyAI();
	void LinkTimeCount(UINT* timeCount);

	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
	virtual void OnCollisionExit(CCollider* target) override;
};

