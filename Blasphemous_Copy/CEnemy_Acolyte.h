#pragma once
#include "CEnemy.h"

class CD2DImage;

class CEnemy_Acolyte : public CEnemy
{
private:
	CD2DImage* m_pImg;

	bool m_bIsAttacking;
	float m_fAtkAccTime;

public:
	CEnemy_Acolyte();
	~CEnemy_Acolyte();

	virtual CEnemy_Acolyte* Clone();
public:
	virtual void update();
	virtual void render();

	virtual void Update_Animation();

	virtual void Init_Animation();

public:
	virtual void Attack();
	virtual void Hit(CGameObject* other);

public:
	virtual void OnCollision(CCollider* other);
};

