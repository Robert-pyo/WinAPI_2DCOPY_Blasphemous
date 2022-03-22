#pragma once
#include "CEffect.h"

class CCollider;

class CEffect_SwordSlash : public CEffect
{
private:
	UINT m_iAttCount;
	fVector2D m_fvDir;
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

	void SetFxDir(fVector2D dir) { m_fvDir = dir; }
	fVector2D GetFxDir() { return m_fvDir; }

public:
	virtual void OnCollisionEnter(CCollider* other);
};

