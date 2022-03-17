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
		CScene* pCurScene = CSceneManager::getInst()->GetCurrentScene();

		if (L"Stage_01" == pCurScene->GetName())
		{
			CHANGE_SCENE(GROUP_SCENE::TOOL);
		}
	}
}
