#pragma once
class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;
	CTexture* m_pMemTex;

	// GDI
	HPEN	m_arrPen[(int)TYPE_PEN::SIZE];
	HBRUSH	m_arrBrush[(int)TYPE_BRUSH::SIZE];

public:
	void update();			// ������ ���� �� �������ְ�
	void render();			// �� ������ �������� ȭ�鿡 �����ش�

	void init();

	HDC GetMainDC();

	void	CreateBrushNPen();
	HPEN	GetPen(TYPE_PEN pen);
	HBRUSH	GetBrush(TYPE_BRUSH brush);
};

