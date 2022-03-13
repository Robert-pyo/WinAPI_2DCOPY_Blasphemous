#pragma once
#include "CGameObject.h"
class CRectangle : public CGameObject
{
private:
	RECT	rect;

public:
	RECT	collisionTop;
	RECT	collisionBottom;
	RECT	collisionLeft;
	RECT	collisionRight;

	CRectangle();
	CRectangle(const float left, const float top, const float right, const float bottom);
	virtual ~CRectangle();

	virtual void update();
	virtual void render(HDC hDC);

	void	SetRect(const float left, const float top, const float right, const float bottom);
	RECT	GetRect();
};

