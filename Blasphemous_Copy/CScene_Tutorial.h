#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Tutorial : public CScene
{
private:
	CD2DImage* m_pBgImage;

public:
	CScene_Tutorial();
	~CScene_Tutorial();

public:
	virtual void update();

public:
	virtual void Enter();
	virtual void Exit();
};

