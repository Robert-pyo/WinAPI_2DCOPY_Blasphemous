#include "framework.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
{
	m_pTex = nullptr;
	m_iIndex = 0;
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::Clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render(HDC hDC)
{
	if (nullptr == m_pTex) return;

	UINT iWidth = m_pTex->GetBmpWidth();
	UINT iHeight = m_pTex->GetBmpHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurX = (m_iIndex % iMaxCol);
	UINT iCurY = (m_iIndex / iMaxCol) % iMaxRow;

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);

	BitBlt(hDC,
		(int)fptRenderPos.x,
		(int)fptRenderPos.y,
		(int)m_fptScale.x,
		(int)m_fptScale.y,
		m_pTex->GetDC(),
		(int)iCurX * SIZE_TILE,
		(int)iCurY * SIZE_TILE,
		SRCCOPY);
}

void CTile::SetTexture(CTexture* pTex)
{
	m_pTex = pTex;
}

void CTile::SetTileIndex(int index)
{
	m_iIndex = index;
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_iIndex, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iIndex, sizeof(int), 1, pFile);
}
