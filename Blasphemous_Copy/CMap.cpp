#include "framework.h"
#include "CMap.h"
#include "CD2DImage.h"

CMap::CMap()
{
    m_pImg = nullptr;
}

CMap::~CMap()
{
}

void CMap::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::GetInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 2.f, m_pImg->GetHeight() * 2.f));
}

CMap* CMap::Clone()
{
    return nullptr;
}

void CMap::update()
{

}

void CMap::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    pos = CCameraManager::GetInst()->GetRenderPos(pos);

    CRenderManager::GetInst()->RenderImage(
        m_pImg,
        pos.x,
        pos.y,
        pos.x + scale.x,
        pos.y + scale.y
    );
}
