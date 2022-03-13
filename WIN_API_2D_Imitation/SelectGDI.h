#pragma once
#include "framework.h"

class SelectGDI
{
private:
	HDC		m_hDC;
	HPEN	m_hOldPen;
	HBRUSH	m_hOldBrush;

public:
	SelectGDI(HDC hDC, TYPE_BRUSH brush)
	{
		m_hDC = hDC;
		HBRUSH hBrush = CCore::getInst()->GetBrush(brush);
		m_hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		m_hOldPen = 0;
	}
	SelectGDI(HDC hDC, TYPE_PEN pen)
	{
		m_hDC = hDC;
		HPEN  hPen = CCore::getInst()->GetPen(pen);
		m_hOldPen = (HPEN)SelectObject(hDC, hPen);
		m_hOldBrush = 0;
	}
	~SelectGDI()
	{
		SelectObject(m_hDC, m_hOldPen);
		SelectObject(m_hDC, m_hOldBrush);
	}
};