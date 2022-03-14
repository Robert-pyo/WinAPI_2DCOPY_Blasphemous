#include "framework.h"
#include "CPlatform.h"
#include "CTexture.h"
#include "CCollider.h"

CPlatform::CPlatform()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Platform_Floor", L"texture\\Map\\Village\\village_sprite_sheet.bmp");

	InitObject(fPoint(190.f, 420.f), fPoint(190.f, 61.f));

	CreateCollider();
	GetCollider()->SetFinalPos(GetPos());
	GetCollider()->SetScale(fPoint(GetScale().x * 2.f, GetScale().y * 2.f - 50.f));
}

CPlatform::~CPlatform()
{
}

CPlatform* CPlatform::Clone()
{
	return new CPlatform(*this);
}

void CPlatform::update()
{
}

void CPlatform::render()
{
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());

	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		fptRenderPos.x - GetScale().x,
		fptRenderPos.y - GetScale().y,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y + GetScale().y,
		341.f, 466.f,
		GetScale().x + 341.f, GetScale().y + 466.f
	);

	component_render();
}