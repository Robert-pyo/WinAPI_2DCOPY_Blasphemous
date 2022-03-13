#include "framework.h"
#include "CRectangle.h"

// ===================== Rectangle =======================
CRectangle::CRectangle()
{
	this->rect.top = 0;
	this->rect.bottom = 0;
	this->rect.left = 0;
	this->rect.right = 0;

	this->collisionLeft = { 0, 0, 0, 0 };
	this->collisionTop = { 0, 0, 0, 0 };
	this->collisionRight = { 0, 0, 0, 0 };
	this->collisionBottom = { 0, 0, 0, 0 };
}

CRectangle::CRectangle(const float left, const float top, const float right, const float bottom)
{
	this->rect.top = (LONG)top;
	this->rect.bottom = (LONG)bottom;
	this->rect.left = (LONG)left;
	this->rect.right = (LONG)right;

	this->collisionLeft = { this->rect.left - 5, this->rect.top, this->rect.left + 5, this->rect.bottom };
	this->collisionTop = { this->rect.left, this->rect.top - 5, this->rect.right, this->rect.top + 5 };
	this->collisionRight = { this->rect.right - 5, this->rect.top, this->rect.right + 5, this->rect.bottom };
	this->collisionBottom = { this->rect.left, this->rect.bottom - 5, this->rect.right, this->rect.bottom + 5 };
}

CRectangle::~CRectangle()
{
}

void CRectangle::update()
{
}

void CRectangle::render(HDC hDC)
{
	Rectangle(hDC, (int)this->m_fptPos.x, (int)this->m_fptPos.y, (int)(this->m_fptPos.x + this->m_fptScale.x), (int)(this->m_fptPos.y + this->m_fptScale.y));
}

void CRectangle::SetRect(const float left, const float top, const float right, const float bottom)
{
	this->rect.left = (LONG)left;
	this->rect.top = (LONG)top;
	this->rect.right = (LONG)right;
	this->rect.bottom = (LONG)bottom;

	this->collisionLeft = { this->rect.left - 5, this->rect.top, this->rect.left + 5, this->rect.bottom };
	this->collisionTop = { this->rect.left, this->rect.top - 5, this->rect.right, this->rect.top + 5 };
	this->collisionRight = { this->rect.right - 5, this->rect.top, this->rect.right + 5, this->rect.bottom };
	this->collisionBottom = { this->rect.left, this->rect.bottom - 5, this->rect.right, this->rect.bottom + 5 };
}

RECT CRectangle::GetRect()
{
	return this->rect;
}