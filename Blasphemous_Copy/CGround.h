#pragma once
#include "CGameObject.h"

class CD2DImage;

class CGround : public CGameObject
{
	CD2DImage* m_pImg;

public:
	CGround();
	virtual ~CGround();
	virtual CGround* Clone();

	virtual void update();
	virtual void render();
};

