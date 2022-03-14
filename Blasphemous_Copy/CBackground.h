#pragma once
#include "CGameObject.h"
class CD2DImage;

class CBackground : public CGameObject
{
private:
	CD2DImage* m_pImg;
	fPoint m_fptTargetTexLT;

public:
	CBackground();
	virtual ~CBackground();

	virtual CBackground* Clone() override;

	virtual void update();
	virtual void render();

	void SetImage(CD2DImage* pImg);
	void SetTexLeftTop(const fPoint leftTop);
};

