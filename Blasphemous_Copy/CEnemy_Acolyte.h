#pragma once
#include "CEnemy.h"

class CD2DImage;

class CEnemy_Acolyte : public CEnemy
{
private:
	CD2DImage* m_pImg;

public:
	CEnemy_Acolyte();
	~CEnemy_Acolyte();

	virtual CEnemy_Acolyte* Clone();
public:
	virtual void update();
	virtual void render();

	virtual void Update_Animation(); 

public:
	virtual void Attack();

public:
	virtual void OnCollision(CCollider* other);
};

