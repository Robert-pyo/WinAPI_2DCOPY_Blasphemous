#pragma once
#include "CEnemy.h"

class CD2DImage;

class CEnemy_Boss_Piedad : public CEnemy
{
private:
	CD2DImage* m_pCutScenePart2;
	CD2DImage* m_pIdleImg;
	CD2DImage* m_pWalkImg;
	CD2DImage* m_pWalkToIdleImg;
	CD2DImage* m_pGroundSmashImg;
	CD2DImage* m_pSlashImg;
	CD2DImage* m_pSpitImg;
	CD2DImage* m_pSpitBackIdleImg;
	CD2DImage* m_pSpitStartImg;
	CD2DImage* m_pStompImg;
	CD2DImage* m_pTurnAroundImg;
	CD2DImage* m_pDeathImg;

	float m_fAtkAccTime;

public:
	CEnemy_Boss_Piedad();
	~CEnemy_Boss_Piedad();

	virtual CEnemy_Boss_Piedad* Clone();

public:
	virtual void update();
	virtual void render();

	virtual void Update_Animation();
	virtual void Init_Animation();

public:
	virtual void Attack();
};

