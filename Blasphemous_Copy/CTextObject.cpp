#include "framework.h"
#include "CTextObject.h"

CTextObject::CTextObject()
{
	initObject(fPoint(0, 0), fPoint(0, 0));
	swprintf_s(lpStr, TEXT(""));
	strSize = 0;
;}

CTextObject::CTextObject(const WCHAR str[128])
{
	initObject(fPoint(WINSIZE_X / 2 - 100, WINSIZE_Y / 2), fPoint(0, 0));
	swprintf_s(lpStr, TEXT("%s"), str);
	strSize = lstrlen(lpStr);
}

CTextObject::CTextObject(const UINT value)
{
	swprintf_s(lpStr, TEXT("%d"), value);
	strSize = lstrlen(lpStr);
}

CTextObject::~CTextObject()
{
}

CTextObject* CTextObject::Clone()
{
	return new CTextObject(*this);
}

void CTextObject::update()
{
	
}

void CTextObject::render(HDC hDC)
{
	TextOutW(hDC, (int)this->m_fptPos.x, (int)this->m_fptPos.y, lpStr, strSize);
}
