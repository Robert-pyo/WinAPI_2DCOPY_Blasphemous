#pragma once
#include "CGameObject.h"
class CTextObject : public CGameObject
{
protected:
	WCHAR	lpStr[128];
	UINT	strSize;

public:
	CTextObject();
	CTextObject(const WCHAR str[128]);
	CTextObject(const UINT value);
	virtual ~CTextObject();
	virtual CTextObject* Clone();

	virtual void update();
	virtual void render(HDC hDC);
};
