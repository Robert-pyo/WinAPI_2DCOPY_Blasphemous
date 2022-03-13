#pragma once
#include "CScene.h"

class CBall;

class CScene_Stage1 : public CScene
{
public:
	CScene_Stage1();
	virtual ~CScene_Stage1();

	virtual void update();

	virtual void Enter() override;
	virtual void Exit() override;
};

