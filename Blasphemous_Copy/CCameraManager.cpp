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
	m_fSpeed = 500.f;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::init()
{
	m_pTex = CResourceManager::getInst()->CreateTexture(L"CamTex", WINSIZE_X, WINSIZE_Y);
}

void CCameraManager::update()
{
	if (m_pTargetObj != nullptr)
	{
		if (m_pTargetObj->IsDisabled())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos());
		}
	}

	CalcDiff();
}

void CCameraManager::render(HDC hDC)
{
	if (CAM_EFFECT::NONE == m_eEffect) return;

	m_fCurTime += (float)fDeltaTime;
	if (m_fEffectDuration < m_fCurTime)
	{
		m_eEffect = CAM_EFFECT::NONE;
		return;
	}

	float fRatio = m_fCurTime / m_fEffectDuration;
	int iAlpha = 0;
	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		iAlpha = (int)(255.f * (1 - fRatio));
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;		// 알파값 조절

	AlphaBlend(hDC
		, 0, 0
		, (int)(m_pTex->GetBmpWidth())
		, (int)(m_pTex->GetBmpHeight())
		, m_pTex->GetDC()
		, 0, 0
		, (int)(m_pTex->GetBmpWidth())
		, (int)(m_pTex->GetBmpHeight())
		, bf);
}

void CCameraManager::SetLookAt(fPoint lookAt)
{
	m_fptLookAt = lookAt;
	m_fptPrevLookAt = m_fptLookAt;

	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();
	m_fTime = fMoveDist / m_fSpeed;
	m_fAccTime = 0;
}

void CCameraManager::FollowTargetObj(CGameObject* targetObj)
{
	m_pTargetObj = targetObj;
}

void CCameraManager::Scroll(fVector2D vec, float velocity)
{
	m_fptLookAt = m_fptLookAt + vec * velocity * (float)fDeltaTime;
	m_fptCurLookAt = m_fptCurLookAt + vec * velocity * (float)fDeltaTime;

	fPoint fptCenter = fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter;
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
