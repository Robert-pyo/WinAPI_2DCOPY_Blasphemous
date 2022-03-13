#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{
public:
	CScene_Start();
	virtual ~CScene_Start();

	virtual void update();

	virtual void Enter() override;
	virtual void Exit() override;
};

