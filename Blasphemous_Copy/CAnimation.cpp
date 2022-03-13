#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
	m_pAnimator		= nullptr;
	m_strAnimName	= L"";
	m_pTex			= nullptr;
	m_iCurFrm		= 0;
	m_fAccTime		= 0.f;
	m_bIsLoop		= false;
	m_bIsDone		= false;
}

CAnimation::~CAnimation()
{
}

void CAnimation::SetName(const wstring& strName)
{
	m_strAnimName = strName;
}

const wstring& CAnimation::GetName()
{
	return m_strAnimName;
}

void CAnimation::SetFrame(int frmIndex)
{
	m_iCurFrm = frmIndex;
}

tAnimFrm& CAnimation::GetFrame(int frmIndex)
{
	return m_vecAnimFrm[frmIndex];
}

void CAnimation::update()
{
	// 시간 축적 > fDuration -> m_iCurFrm++
	m_fAccTime += fDeltaTime;

	if (m_fAccTime >= m_vecAnimFrm[m_iCurFrm].fDuration)
	{
		// 축적 시간 -> fDuration 만큼 다시 빼줌 -> 0으로 초기화보다는 정확
		m_fAccTime -= m_vecAnimFrm[m_iCurFrm].fDuration;

		m_iCurFrm++;

		if (m_bIsLoop)
		{
			// 애니메이션에 끝에 도달했으면 처음 프레임으로 돌아감
			m_iCurFrm %= m_vecAnimFrm.size();
		}
		else
		{
			if (m_iCurFrm == m_vecAnimFrm.size())
			{
				m_iCurFrm = (int)m_vecAnimFrm.size() - 1;
				m_bIsDone = true;
			}
		}
	}
}

void CAnimation::render(HDC hDC)
{
	CGameObject* pObj = m_pAnimator->GetOwnerObj();
	// 그릴 위치
	fPoint fptDrawPos = pObj->GetPos();
	// 현재 그려야할 프레임의 애니메이션
	tAnimFrm animFrm = m_vecAnimFrm[m_iCurFrm];

	fptDrawPos = fptDrawPos + animFrm.fptOffset;

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(fptDrawPos);

	TransparentBlt(hDC,
		(int)(fptRenderPos.x - animFrm.fptTexScale.x),
		(int)(fptRenderPos.y - animFrm.fptTexScale.y),
		(int)(animFrm.fptTexScale.x * 2),
		(int)(animFrm.fptTexScale.y * 2),
		m_pTex->GetDC(),
		(int)animFrm.fptLeftTop.x,
		(int)animFrm.fptLeftTop.y,
		(int)animFrm.fptTexScale.x,
		(int)animFrm.fptTexScale.y,
		RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* pTex,		// 애니메이션의 이미지
						fPoint leftTop,		// 애니메이션 시작 프레임 좌상단 좌표
						fPoint scale,		// 애니메이션 프레임의 크기
						fPoint step,		// 애니메이션 프레임 반복 위치
						float duration,		// 애니메이션 프레임 지속 시간
						UINT frmCount)		// 애니메이션 프레임 개수
{
	m_pTex = pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < frmCount; ++i)
	{
		frm.fDuration = duration;	// 지속 시간
		frm.fptTexScale = scale;	// 텍스쳐의 크기
		// leftTop + 다음 프레임 이미지까지의 거리 * 현재 프레임 카운트
		frm.fptLeftTop = leftTop + step * i;

		m_vecAnimFrm.push_back(frm);
	}
}

void CAnimation::SetLoop(bool isLoop)
{
	m_bIsLoop = isLoop;
}

void CAnimation::SetAnimDone(bool isDone)
{
	m_bIsDone = isDone;
}

bool CAnimation::GetAnimDone()
{
	return m_bIsDone;
}