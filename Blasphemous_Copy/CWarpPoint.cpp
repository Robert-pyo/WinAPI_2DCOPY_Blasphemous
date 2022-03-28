#include "framework.h"
#include "CWarpPoint.h"
#include "CCollider.h"
#include "CScene.h"

CWarpPoint::CWarpPoint()
{
	SetScale(fPoint(100.f, 100.f));

	CreateCollider();
	GetCollider()->SetScale(GetScale());
}

CWarpPoint::~CWarpPoint()
{
}

CWarpPoint* CWarpPoint::Clone()
{
	return new CWarpPoint(*this);
}

void CWarpPoint::update()
{
}

void CWarpPoint::render()
{
	component_render();
}

void CWarpPoint::OnCollisionEnter(CCollider* other)
{
	if (L"Player" == other->GetOwnerObj()->GetName())
	{
		if (L"Tutorial" == GetName())
		{
			ChangeToNextScene(GROUP_SCENE::TUTORIAL);
		}
		else if (L"Church" == GetName())
		{
			ChangeToNextScene(GROUP_SCENE::CHURCH);
		}
		else if (L"Boss" == GetName())
		{
			//ChangeToNextScene(GROUP_SCENE::BOSSSTAGE);
		}
	}
}
