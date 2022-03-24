#pragma once
#include "CGameObject.h"

class CD2DImage;

class CMap : public CGameObject
{
public:
	CD2DImage* m_pImg;

	CMap();
	~CMap();

	void Load(wstring strKey, wstring strPath);

	virtual CMap* Clone();
	virtual void update();
	virtual void render();
};

