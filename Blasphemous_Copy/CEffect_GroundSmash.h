#pragma once
#include "CEffect.h"
class CEffect_GroundSmash : public CEffect
{
private:
	float m_fFxAccTime;

public:
	CEffect_GroundSmash();
	~CEffect_GroundSmash();

	virtual CEffect_GroundSmash* Clone();

public:
	virtual void update() final;
	virtual void render() final;

public:
	virtual void OnCollisionEnter(CCollider* other);
};

