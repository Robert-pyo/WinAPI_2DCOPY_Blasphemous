#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_End : public CScene
{
private:
	CD2DImage* m_pBGImg;

	float m_fInputDelay;

public:
	CScene_End();
	~CScene_End();

public:
	virtual void update();

	virtual void init();

public:
	virtual void Enter();
	virtual void Exit();
};

