#include "framework.h"
#include "CCollider.h"
#include "CGameObject.h"

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

UINT CCollider::GetCollisionCount()
{
	return m_iCollisionCount;
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

void CCollider::render()
{
	COLORREF rgb = RGB(0, 0, 0);
	if (m_iCollisionCount)
		rgb = RGB(255, 0, 0);
	else
		rgb = RGB(0, 255, 0);

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(m_fptFinalPos);

	CRenderManager::GetInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2.f,
		fptRenderPos.y - m_fptScale.y / 2.f,
		fptRenderPos.x + m_fptScale.x / 2.f,
		fptRenderPos.y + m_fptScale.y / 2.f,
		rgb);
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
