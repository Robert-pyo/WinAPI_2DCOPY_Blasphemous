#include "framework.h"
#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTexture.h"

CCameraManager::CCameraManager()
{
	m_fptLookAt		= {};
	m_pTargetObj	= nullptr;

	m_fTime = 2.f;
	m_fAccTime = m_fTime;
	m_fSpeed = 350.f;

	m_pImg = nullptr;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::init()
{
	m_pImg = CResourceManager::getInst()->CreateTexture(L"CamTex", WINSIZE_X, WINSIZE_Y);
}

void CCameraManager::update()
{
	if (m_bHasBoundary)
	{
		CheckBoundary();
	}
	else 
	{
		if (m_pTargetObj != nullptr)
		{
			if (m_pTargetObj->IsDisabled())
			{
				m_pTargetObj = nullptr;
			}
			else
			{
				if (m_bFollowX)
					m_fptLookAt.x = m_pTargetObj->GetPos().x;

				if (m_bFollowY)
					m_fptLookAt.y = m_pTargetObj->GetPos().y;
			}
		}
	}

	CalcDiff();
}

void CCameraManager::render()
{
	if (CAM_EFFECT::NONE == m_eEffect) return;

	m_fCurTime += (float)fDeltaTime;
	if (m_fEffectDuration < m_fCurTime)
	{
		m_eEffect = CAM_EFFECT::NONE;
		return;
	}

	float fRatio = m_fCurTime / m_fEffectDuration;
	float fAlpha = 0;
	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		fAlpha = fRatio;
	}
	else if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		fAlpha = 1.f - fRatio;
	}

	CRenderManager::getInst()->RenderFillRectangle(
		-1.f, -1.f, 
		WINSIZE_X + 1, WINSIZE_Y + 1,
		D2D1::ColorF(0.f, 0.f, 0.f, fAlpha)
	);
}

void CCameraManager::InitCameraPos(fPoint pos)
{
	m_fptPrevLookAt = pos;
}

void CCameraManager::SetLookAt(fPoint lookAt)
{
	m_fptLookAt = lookAt;
	//m_fptPrevLookAt = m_fptLookAt;

	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();
	m_fTime = fMoveDist / m_fSpeed;
	m_fAccTime = 0;
}

void CCameraManager::FollowTargetObj(CGameObject* targetObj, bool flwX, bool flwY)
{
	m_pTargetObj = targetObj;
	m_bFollowX = flwX;
	m_bFollowY = flwY;
}

void CCameraManager::Scroll(fVector2D vec, float velocity)
{
	m_fptLookAt = m_fptLookAt + vec * velocity * (float)fDeltaTime;
	m_fptCurLookAt = m_fptCurLookAt + vec * velocity * (float)fDeltaTime;

	fPoint fptCenter = fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter;
}

void CCameraManager::SetBoundary(fPoint leftTop, fPoint rightBtm)
{
	m_bHasBoundary = true;

	m_fptBoundaryLT = leftTop;
	m_fptBoundaryRB = rightBtm;
}

void CCameraManager::SetBoundary(bool hasBoundary)
{
	m_bHasBoundary = hasBoundary;
}

fPoint CCameraManager::GetLookAt()
{
	return m_fptLookAt;
}

fPoint CCameraManager::GetRenderPos(fPoint objPos)
{
	return objPos - m_fptDiff;
}

fPoint CCameraManager::GetRealPos(fPoint renderPos)
{
	return renderPos + m_fptDiff;
}

// 화면 중앙과 카메라 LookAt 좌표 사이의 차이 계산
void CCameraManager::CalcDiff()
{
	m_fAccTime += fDeltaTime;

	// 목적지 좌표 - 이전 카메라 좌표 -> 방향벡터 나옴
	fVector2D fv_lookDir = m_fptLookAt - m_fptPrevLookAt;

	if (m_fTime <= m_fAccTime)
	{
		m_fptCurLookAt = m_fptLookAt;
	}
	else
	{
		m_fptCurLookAt = m_fptPrevLookAt + fv_lookDir.Normalize() * m_fSpeed * fDeltaTime;
		m_fptPrevLookAt = m_fptCurLookAt;
	}

	fPoint fptCenter = fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter;
}

void CCameraManager::LerpDiff(fPoint targetPos)
{
	if (targetPos.x == 0 && targetPos.y == 0)
	{
		m_fptLerpDiff = m_pTargetObj->GetPos();
		return;
	}

	float x = (targetPos.x - m_pTargetObj->GetPos().x) / 2.f;
	float y = (targetPos.y - m_pTargetObj->GetPos().y) / 2.f;
	m_fptLerpDiff = fPoint(x, y);
}

void CCameraManager::CheckBoundary()
{
	if (m_pTargetObj != nullptr)
	{
		if (m_bFollowX)
			m_fptLookAt.x = m_pTargetObj->GetPos().x;

		if (m_bFollowY)
			m_fptLookAt.y = m_pTargetObj->GetPos().y;
	}

	if (m_fptLookAt.x - WINSIZE_X / 2.f < m_fptBoundaryLT.x)
	{
		m_fptLookAt.x = m_fptBoundaryLT.x + WINSIZE_X / 2.f;
	}

	if (m_fptLookAt.y - WINSIZE_Y / 2.f < m_fptBoundaryLT.y)
	{
		m_fptLookAt.y = m_fptBoundaryLT.y + WINSIZE_Y / 2.f;
	}

	if (m_fptLookAt.x + WINSIZE_X / 2.f > m_fptBoundaryRB.x)
	{
		m_fptLookAt.x = m_fptBoundaryRB.x - WINSIZE_X / 2.f;
	}

	if (m_fptLookAt.y + WINSIZE_Y / 2.f > m_fptBoundaryRB.y)
	{
		m_fptLookAt.y = m_fptBoundaryRB.y - WINSIZE_Y / 2.f;
	}

	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();
	m_fTime = fMoveDist / m_fSpeed;
	m_fAccTime = 0;
}

fPoint CCameraManager::GetLerpPoint()
{
	return m_fptLerpDiff;
}

void CCameraManager::FadeIn(float duration)
{
	m_eEffect = CAM_EFFECT::FADE_IN;
	m_fEffectDuration = duration;
	m_fCurTime = 0.f;
}

void CCameraManager::FadeOut(float duration)
{
	m_eEffect = CAM_EFFECT::FADE_OUT;
	m_fEffectDuration = duration;
	m_fCurTime = 0.f;
}
