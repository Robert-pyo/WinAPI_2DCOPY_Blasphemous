#include "framework.h"
#include "CEffect.h"

CEffect::CEffect()
{
	m_pFxImg = nullptr;
	m_pOwner = nullptr;
	m_fFxDuration = 0.f;
	m_bIsStart = false;
}

CEffect::~CEffect()
{
}

//CEffect* CEffect::Clone()
//{
//	return new CEffect(*this);
//}

void CEffect::LoadEffectImg(const wstring& strKey, const wstring& strRelativePath)
{
	m_pFxImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strRelativePath);
}
