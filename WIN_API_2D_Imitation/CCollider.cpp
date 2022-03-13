#include "framework.h"
#include "CCollider.h"
#include "CGameObject.h"
#include "SelectGDI.h"

UINT CCollider::s_iUID = 0;

CCollider::CCollider()
{
	m_pOwner = nullptr;
	m_fptFinalPos = {};
	m_fptOffsetPos = {};
	m_fptScale = {};
	m_iCollisionCount = 0;

	m_iUID = s_iUID++;
}

CCollider::CCollider(const CCollider& other)
{
	m_pOwner = other.m_pOwner;
	m_fptFinalPos = other.m_fptFinalPos;
	m_fptOffsetPos = other.m_fptOffsetPos;
	m_fptScale = other.m_fptScale;

	m_iUID = s_iUID++;
}

CCollider::~CCollider()
{

}

fPoint CCollider::GetFinalPos()
{
	return m_fptFinalPos;
}

fPoint CCollider::GetOffsetPos()
{
	return m_fptOffsetPos;
}

fPoint CCollider::GetScale()
{
	return m_fptScale;
}

RECT CCollider::GetBorderPos()
{
	return m_rtCollider;
}

UINT CCollider::GetID()
{
	return m_iUID;
}

void CCollider::SetFinalPos(fPoint pos)
{
	m_fptFinalPos = pos;
}

void CCollider::SetOffsetPos(fPoint offset)
{
	m_fptOffsetPos = offset;
}

void CCollider::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

void CCollider::finalUpdate()
{
	fPoint fptObjPos = m_pOwner->GetPos();
	m_fptFinalPos = fptObjPos + m_fptOffsetPos;

	m_rtCollider.left = (LONG)(m_fptFinalPos.x - m_fptScale.x / 2.f);
	m_rtCollider.right = (LONG)(m_fptFinalPos.x + m_fptScale.x / 2.f);
	m_rtCollider.top = (LONG)(m_fptFinalPos.y - m_fptScale.y / 2.f);
	m_rtCollider.bottom = (LONG)(m_fptFinalPos.y + m_fptScale.y / 2.f);
}

void CCollider::render(HDC hDC)
{
	TYPE_PEN penType;

	if (m_iCollisionCount > 0)
	{
		penType = TYPE_PEN::RED;
	}
	else
	{
		penType = TYPE_PEN::BLUE;
	}

	SelectGDI pen(hDC, penType);
	SelectGDI brush(hDC, TYPE_BRUSH::HOLLOW);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptFinalPos);

	Rectangle(hDC,
		(int)(fptRenderPos.x - m_fptScale.x / 2.f),
		(int)(fptRenderPos.y - m_fptScale.y / 2.f),
		(int)(fptRenderPos.x + m_fptScale.x / 2.f),
		(int)(fptRenderPos.y + m_fptScale.y / 2.f)
	);
}

CGameObject* CCollider::GetOwnerObj()
{
	return m_pOwner;
}

void CCollider::OnCollision(CCollider* target)
{
	m_pOwner->OnCollision(target);
}

void CCollider::OnCollisionEnter(CCollider* target)
{
	m_pOwner->OnCollisionEnter(target);
	m_iCollisionCount++;
}

void CCollider::OnCollisionExit(CCollider* target)
{
	m_pOwner->OnCollisionExit(target);

	if (m_iCollisionCount > 0)
		m_iCollisionCount--;
}
