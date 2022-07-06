#pragma once
#include "CEffect.h"
class CEffect_WoodThorn : public CEffect
{
private:
	float m_fFxAccTime;
	float m_fSpikeSpeed;

	float m_fDurationPerFrame;

	bool m_bIsSpikeDone;

public:
	CEffect_WoodThorn();
	~CEffect_WoodThorn();

	virtual CEffect_WoodThorn* Clone();

public:
	virtual void update() final;
	virtual void render() final;

public:
	virtual void OnCollisionEnter(CCollider* other);
};

