#include "framework.h"
#include "CText_Score.h"

CText_Score::CText_Score()
{
	initObject(fPoint(WINSIZE_X / 2 - 50, 50), fPoint(0, 0));
	this->playerScore	= 0;
	this->enemyScore	= 0;
	this->pBall			= nullptr;
}

CText_Score::~CText_Score()
{
}

void CText_Score::update()
{
	AddScore();
}

void CText_Score::render(HDC hDC)
{
	swprintf_s(lpStr, TEXT("%d"), playerScore);
	strSize = lstrlen(lpStr);
	TextOutW(hDC, (int)this->m_fptPos.x, (int)this->m_fptPos.y, lpStr, strSize);

	TextOutW(hDC, (int)this->m_fptPos.x + 25, (int)this->m_fptPos.y, TEXT(" : "), 3);

	swprintf_s(lpStr, TEXT("%d"), enemyScore);
	strSize = lstrlen(lpStr);
	TextOutW(hDC, (int)this->m_fptPos.x + 50, (int)this->m_fptPos.y, lpStr, strSize);
}

void CText_Score::SetScoreBall(CBall* _pBall)
{
	this->pBall = _pBall;
}

void CText_Score::AddScore()
{
	if (this->pBall->playerScored)
	{
		playerScore++;
		this->pBall->playerScored = false;
	}
	else if (this->pBall->enemyScored)
	{
		enemyScore++;
		this->pBall->enemyScored = false;
	}
}
