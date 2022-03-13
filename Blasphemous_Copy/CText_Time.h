#pragma once
#include "CTextObject.h"
class CText_Time : public CTextObject
{
public:
	unsigned int secondCount;

	CText_Time();
	virtual ~CText_Time();
	virtual CText_Time* Clone();

	virtual void update();

	void CountTime();
};

