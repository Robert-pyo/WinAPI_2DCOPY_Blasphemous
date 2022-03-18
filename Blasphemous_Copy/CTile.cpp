#include "framework.h"
#include "CTile.h"
#include "CD2DImage.h"

CTile::CTile()
{
	m_pImg = nullptr;
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

void CTile::render()
{
	if (nullptr == m_pImg) return;

	UINT iWidth = m_pImg->GetWidth();
	UINT iHeight = m_pImg->GetHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurX = (m_iIndex % iMaxCol);
	UINT iCurY = (m_iIndex / iMaxCol) % iMaxRow;

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(GetPos());
	fPoint fptScale = GetScale();

	CRenderManager::GetInst()->RenderFrame(
		m_pImg,
		fptRenderPos.x,
		fptRenderPos.y,
		fptScale.x,
		fptScale.y,
		iCurX * fptScale.x,
		iCurY * fptScale.y,
		fptScale.x,
		fptScale.y
	);
}

void CTile::SetTexture(CD2DImage* pImg)
{
	m_pImg = pImg;
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
