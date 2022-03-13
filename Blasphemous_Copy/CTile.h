#pragma once
#include "CGameObject.h"

class CTexture;

class CTile : public CGameObject
{
private:
	CTexture* m_pTex;
	int m_iIndex;

public:
	const static int SIZE_TILE = 32;

	CTile();
	virtual ~CTile();

	virtual CTile* Clone();

	virtual void update();
	virtual void render(HDC hDC);

	void SetTexture(CTexture* pTex);
	void SetTileIndex(int index);

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

