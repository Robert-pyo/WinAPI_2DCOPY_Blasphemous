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
	if (nullptr == m_pImg) return;

	fPoint fptPos = GetPos();
	fPoint fptScale = GetScale();
	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(fptPos);

	if (GetObjGroup() == GROUP_GAMEOBJ::BACKGROUND_BACK)
	{
		CRenderManager::GetInst()->RenderFrame(
			m_pImg,
			fptPos.x,
			fptPos.y,
			fptPos.x + WINSIZE_X,
			fptPos.y + WINSIZE_Y - 100.f,
			m_fptTargetTexLT.x,
			m_fptTargetTexLT.y,
			m_fptTargetTexLT.x + fptScale.x,
			m_fptTargetTexLT.y + fptScale.y
		);
	}
	else if (GetObjGroup() == GROUP_GAMEOBJ::BACKGROUND_MIDDLE)
	{
		fptRenderPos.x = fptPos.x + (fptRenderPos.x - fptPos.x) / 5.f;

		CRenderManager::GetInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x,
			fptRenderPos.y - WINSIZE_Y / 2.f,
			fptRenderPos.x + fptScale.x * 2.f,
			fptRenderPos.y + WINSIZE_Y / 1.5f,
			m_fptTargetTexLT.x,
			m_fptTargetTexLT.y,
			m_fptTargetTexLT.x + fptScale.x,
			m_fptTargetTexLT.y + fptScale.y
		);
	}
	else if (GetObjGroup() == GROUP_GAMEOBJ::BACKGROUND_FRONT)
	{
		CRenderManager::GetInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x,
			fptRenderPos.y - WINSIZE_Y / 2.f,
			fptRenderPos.x + fptScale.x * 2.f,
			fptRenderPos.y + WINSIZE_Y / 1.5f,
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
