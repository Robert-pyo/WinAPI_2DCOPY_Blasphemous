#pragma once
#include "CScene.h"

class CD2DImage;

class CScene_Title : public CScene
{
private:
	CD2DImage* m_pBackImgFront;
	CD2DImage* m_pBackImgMiddle;
	CD2DImage* m_pBackImgBack;

	vector<CUI*> m_vecUI;

public:
	CScene_Title();
	~CScene_Title();

public:
	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

