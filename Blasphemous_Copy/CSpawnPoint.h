#pragma once
#include "CGameObject.h"

class CSpawnPoint : public CGameObject
{
public:
	CSpawnPoint();
	virtual ~CSpawnPoint();

	virtual CSpawnPoint* Clone();

public:
	virtual void update();
	virtual void render();
};

