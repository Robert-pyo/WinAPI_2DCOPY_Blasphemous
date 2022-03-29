#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Boss : public CScene
{
private:
	CD2DImage* m_pBgImg;

public:
	CScene_Boss();
	~CScene_Boss();

public:
	virtual void update();

	virtual void init();

public:
	virtual void Enter();
	virtual void Exit();
};

