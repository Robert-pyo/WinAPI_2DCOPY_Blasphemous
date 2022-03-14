#include "framework.h"
#include "CBackground.h"
#include "CTexture.h"

CBackground::CBackground()
{
	m_pImg = nullptr;

	InitObject(fPoint(0.f, 0.f), fPoint(0.f, 0.f));
}

CBackground::~CBackground()
{
}

CBackground* CBackground::Clone()
{
	return new CBackground(*this);
}

void CBackground::update()
{

}

void CBackground::render()
{
	fPoint fptPos = GetPos();
	fPoint fptScale = GetScale();

	if (GetObjGroup() == GROUP_GAMEOBJ::BACKGROUND_BACK)
	{
		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			fptPos.x - fptScale.x / 2.f,
			fptPos.y - fptScale.y / 2.f,
			fptPos.x + WINSIZE_X,
			fptPos.y + WINSIZE_Y,
			m_fptTargetTexLT.x,
			m_fptTargetTexLT.y,
			m_fptTargetTexLT.x + fptScale.x,
			m_fptTargetTexLT.y + fptScale.y
		);
	}
	else if (GetObjGroup() == GROUP_GAMEOBJ::BACKGROUND_MIDDLE)
	{
		fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(fptPos);
		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x - fptScale.x / 2.f,
			fptPos.y - fptScale.y / 2.f,
			fptRenderPos.x + WINSIZE_X,
			fptPos.y + WINSIZE_Y,
			m_fptTargetTexLT.x,
			m_fptTargetTexLT.y,
			m_fptTargetTexLT.x + fptScale.x,
			m_fptTargetTexLT.y + fptScale.y
		);
	}

	component_render();
}

void CBackground::SetImage(CD2DImage* pImg)
{
	m_pImg = pImg;
}

void CBackground::SetTexLeftTop(const fPoint leftTop)
{
	m_fptTargetTexLT = leftTop;
}
