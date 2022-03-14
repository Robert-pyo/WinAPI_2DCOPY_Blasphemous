#pragma once
class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;

public:
	void update();			// 정보를 저장 및 갱신해주고
	void render();			// 그 정보를 바탕으로 화면에 보여준다

	void init();

	HDC GetMainDC();
};

