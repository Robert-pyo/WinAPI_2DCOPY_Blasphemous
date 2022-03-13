#pragma once
#include "CRectangle.h"

#define INIT_VELOCITY (400.0f)

class CBall : public CRectangle
{
private:
	float m_fVelocity;
	vector<CRectangle*> collisionTarget;
	fVector2D m_fvMoveDir;
	vector<CBall*> generatedBall;

public:
	bool playerScored;
	bool enemyScored;

	CBall();
	virtual ~CBall();

	virtual void	update();
	virtual void	render(HDC hDC);

	//void IsTouched(CRectangle* target);
	void SetCollisionTarget(CRectangle* target);

	//void GenerateBall();
};

