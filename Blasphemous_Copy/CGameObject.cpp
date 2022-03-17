#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"

void CGameObject::SetDisable()
{
	m_bIsActive = false;
}

CGameObject::CGameObject()
{
	m_strName		= L"";
	m_fptPos		= { 0.0f, 0.0f };
	m_fptScale		= { 0.0f, 0.0f };
	m_pCollider		= nullptr;
	m_pAnimator		= nullptr;
	m_bIsActive		= true;
	objGroup		= GROUP_GAMEOBJ::DEFAULT;
}

CGameObject::CGameObject(const CGameObject& other)
{
	m_strName	= other.m_strName;
	m_fptPos	= other.m_fptPos;
	m_fptScale	= other.m_fptScale;
	m_bIsActive = true;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;

	if (nullptr != other.m_pCollider)
	{
		m_pCollider = new CCollider(*other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (nullptr != other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CGameObject::~CGameObject()
{
	// 컴포넌트 삭제

	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void CGameObject::finalUpdate()
{
	if (nullptr != m_pCollider)
		m_pCollider->finalUpdate();
}

void CGameObject::component_render()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}
	if (nullptr != m_pCollider)
	{
		m_pCollider->render();
	}
}

void CGameObject::InitObject(const fPoint m_fptPos, const fPoint m_fptScale)
{
	this->m_fptPos		= m_fptPos;
	this->m_fptScale	= m_fptScale;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

void CGameObject::SetName(const wstring& name)
{
	m_strName = name;
}

void CGameObject::SetPos(const fPoint& m_fptPos)
{
	this->m_fptPos.x = m_fptPos.x;
	this->m_fptPos.y = m_fptPos.y;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

bool CGameObject::IsDisabled()
{
	return !m_bIsActive;
}

CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

CAnimator* CGameObject::GetAnimator()
{
	return m_pAnimator;
}

void CGameObject::SetScale(const fPoint& m_fptScale)
{
	this->m_fptScale.x = m_fptScale.x;
	this->m_fptScale.y = m_fptScale.y;
}

void CGameObject::SetObjGroup(const GROUP_GAMEOBJ& type)
{
	this->objGroup = type;
}

GROUP_GAMEOBJ CGameObject::GetObjGroup()
{
	return objGroup;
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator();
	m_pAnimator->m_pOwner = this;
}
