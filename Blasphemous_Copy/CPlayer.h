#pragma once
#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImg;

	fVector2D m_fvDir;
	fVector2D m_fvChangeXY;

	float m_fVelocity;
	float m_fAccel;
	float m_fJumpPower;

	bool m_bIsJumping;
	bool m_bIsGrounded;

public:
	CPlayer();
	virtual ~CPlayer();

	virtual CPlayer* Clone() override;

	virtual void update() final;
	virtual void render();

	void Jump();

	const float		 GetVelocity();
	const fVector2D& GetDirVector();

	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
	virtual void OnCollisionExit(CCollider* target) override;
};

