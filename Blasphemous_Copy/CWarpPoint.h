#pragma once
#include "CGameObject.h"
class CWarpPoint : public CGameObject
{
public:
	CWarpPoint();
	~CWarpPoint();

	virtual CWarpPoint* Clone();

	virtual void update();
	virtual void render();

	virtual void OnCollisionEnter(CCollider* other);
};

