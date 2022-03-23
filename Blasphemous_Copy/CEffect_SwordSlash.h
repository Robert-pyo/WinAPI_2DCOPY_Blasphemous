#pragma once
#include "CEffect.h"

class CCollider;

class CEffect_SwordSlash : public CEffect
{
private:
	UINT m_iAttCount;
public:
	CEffect_SwordSlash();
	~CEffect_SwordSlash();

	virtual CEffect_SwordSlash* Clone();

public:
	virtual void update() final;
	virtual void render() final;

public:
	UINT GetAttCount() { return m_iAttCount; }
	void SetAttCount(UINT count) { m_iAttCount = count; }

public:
	virtual void OnCollisionEnter(CCollider* other);
};

