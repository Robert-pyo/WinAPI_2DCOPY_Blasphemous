#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Church : public CScene
{
private:
	map<string, fPoint> m_mapSpawnPoint;

public:
	CScene_Church();
	~CScene_Church();

public:
	virtual void update();

	virtual void init();

public:
	virtual void Enter();
	virtual void Exit();
};

