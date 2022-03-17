#include "framework.h"
#include "CWarpPoint.h"
#include "CCollider.h"

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
}

void CWarpPoint::OnCollisionEnter(CCollider* other)
{
	if (L"Player" == other->GetOwnerObj()->GetName())
	{
		
	}
}
