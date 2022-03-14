#pragma once
#include "CGameObject.h"

class CTexture;
class CD2DImage;

class CTile : public CGameObject
{
private:
	CD2DImage* m_pImg;
	int m_iIndex;

public:
	const static int SIZE_TILE = 32;

	CTile();
	virtual ~CTile();

	virtual CTile* Clone();

	virtual void update();
	virtual void render();

	void SetTexture(CD2DImage* pImg);
	void SetTileIndex(int index);

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

