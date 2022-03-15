#pragma once
#include "CGameObject.h"

class CD2DImage;

class CPrayerTable : public CGameObject
{
private:
	CD2DImage* m_pImg;
	
	bool m_bIsActive;

public:
	CPrayerTable();
	~CPrayerTable();

	virtual CPrayerTable* Clone();

	virtual void update() override;
	virtual void render() override;
};

