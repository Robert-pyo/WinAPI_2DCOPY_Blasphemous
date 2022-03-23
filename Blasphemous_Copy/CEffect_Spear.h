#pragma once
#include "CEffect.h"
class CEffect_Spear : public CEffect
{
public:
	CEffect_Spear();
	~CEffect_Spear();

	virtual CEffect_Spear* Clone();

public:
	virtual void update() final;
	virtual void render() final;

public:
	virtual void OnCollisionEnter(CCollider* other);
};

