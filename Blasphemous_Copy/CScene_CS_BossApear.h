#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_CS_BossApear : public CScene
{
private:
	CD2DImage* m_pBgImg;

public:
	CScene_CS_BossApear();
	~CScene_CS_BossApear();

public:
	virtual void init();

public:
	virtual void Enter();
	virtual void Exit();
};

