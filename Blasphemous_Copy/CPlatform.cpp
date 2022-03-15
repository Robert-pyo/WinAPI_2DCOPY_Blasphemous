#include "framework.h"
#include "CPlatform.h"
#include "CTexture.h"
#include "CCollider.h"

CPlatform::CPlatform()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Platform_Floor", L"texture\\Map\\TutorialScene\\Floor\\brotherhood_floor.png");

	InitObject(fPoint(627.f, 370.f), fPoint(403.f, 110.f));

	CreateCollider();
	GetCollider()->SetFinalPos(GetPos());
	GetCollider()->SetOffsetPos(fPoint(0.f, 60.f));
	GetCollider()->SetScale(fPoint(GetScale().x * 2.f, GetScale().y - 10.f));
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
		fptRenderPos.y - GetScale().y * 1.3f,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y + GetScale().y,
		0.f, 0.f,
		GetScale().x, GetScale().y
	);

	component_render();
}