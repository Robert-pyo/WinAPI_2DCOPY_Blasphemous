#pragma once
#include "CTextObject.h"
#include "CBall.h"

class CText_Score : public CTextObject
{
private:
	USHORT playerScore;
	USHORT enemyScore;

	CBall* pBall;

public:
	CText_Score();
	virtual ~CText_Score();

	virtual void update() final;
	virtual void render(HDC hDC) final;

	void SetScoreBall(CBall* _pBall);
private:
	void AddScore();
};

