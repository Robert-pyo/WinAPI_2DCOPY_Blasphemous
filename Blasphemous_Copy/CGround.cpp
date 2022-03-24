#include "framework.h"
#include "CGround.h"
#include "CTexture.h"
#include "CCollider.h"

CGround::CGround()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Platform_Floor", L"texture\\Map\\TutorialScene\\Floor\\brotherhood_floor.png");

	InitObject(fPoint(627.f, 370.f), fPoint(403.f, 110.f));

	CreateCollider();
	GetCollider()->SetFinalPos(GetPos());
	GetCollider()->SetOffsetPos(fPoint(0.f, 60.f));
	GetCollider()->SetScale(fPoint(GetScale().x * 2.f, GetScale().y - 10.f));
}

CGround::~CGround()
{
}

CGround* CGround::Clone()
{
	return new CGround(*this);
}

void CGround::update()
{
}

void CGround::render()
{
	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(GetPos());

	CRenderManager::GetInst()->RenderFrame(
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