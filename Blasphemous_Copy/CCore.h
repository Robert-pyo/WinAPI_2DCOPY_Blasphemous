#pragma once
class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;

public:
	void update();			// ������ ���� �� �������ְ�
	void render();			// �� ������ �������� ȭ�鿡 �����ش�

	void init();

	HDC GetMainDC();
};

