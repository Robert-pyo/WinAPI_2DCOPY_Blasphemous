#pragma once
#include "CGameObject.h"

class AI;

class CEnemy : public CGameObject
{
private:
	AI* m_pAI;

	float	m_fVelocity;
	float	m_fAccelGravity;

	fVector2D m_fvCurDir;
	fVector2D m_fvPrevDir;

	bool	m_bIsGrounded;
public:
	CEnemy();
	virtual ~CEnemy();
	virtual CEnemy* Clone();

	virtual void update();
	virtual void render();

	float GetVelocity();

	void SetAI(AI* pAI);
	void SetVelocity(float fVelocity);

	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
};

