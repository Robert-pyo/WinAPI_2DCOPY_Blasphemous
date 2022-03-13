#include "framework.h"
#include "CText_Time.h"

CText_Time::CText_Time()
{
	initObject(fPoint(50, 50), fPoint(0, 0));
	secondCount = 0;
}

CText_Time::~CText_Time()
{
}

CText_Time* CText_Time::Clone()
{
	return new CText_Time(*this);
}

void CText_Time::update()
{
	CountTime();
}

void CText_Time::CountTime()
{
	static double updateCount = 0;
	updateCount += fDeltaTime;
	if (updateCount >= 1.0)
	{
		secondCount++;
		updateCount = 0;
	}

	swprintf_s(lpStr, TEXT("%d"), secondCount);
	strSize = lstrlen(lpStr);
}