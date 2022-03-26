#pragma once
#include "CEffect.h"

class CCollider;

class CEffect_Rock : public CEffect
{
private:
	float m_fSpeed;
	float m_fFxAccTime;

public:
	CEffect_Rock();
	~CEffect_Rock();

	virtual CEffect_Rock* Clone();

public:
	virtual void update();
	virtual void render();

	void init();

public:
	virtual void OnCollisionEnter(CCollider* other);
};

