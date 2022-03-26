#pragma once
#include "CEnemy.h"
class CEnemy_Stoner : public CEnemy
{
private:
	float m_fAtkAccTime;
public:
	CEnemy_Stoner();
	~CEnemy_Stoner();

	virtual CEnemy_Stoner* Clone();

public:
	virtual void update();
	virtual void render();

	virtual void Update_Animation();
	virtual void Init_Animation();

public:
	virtual void Attack();
};

