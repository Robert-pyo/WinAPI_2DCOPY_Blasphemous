#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
	m_pAnimator		= nullptr;
	m_strAnimName	= L"";
	m_pImg			= nullptr;
	m_iCurFrm		= 0;
	m_fAccTime		= 0.f;
	m_fCurAnimDuration = 0.f;
	m_bIsLoop		= false;
	m_bIsAnimDone	= false;
}

CAnimation::CAnimation(const CAnimation& pOther)
{
	m_strAnimName = pOther.m_strAnimName;
	for (int i = 0; i < pOther.m_vecAnimFrm.size(); i++)
	{
		m_vecAnimFrm.push_back(pOther.m_vecAnimFrm[i]);
	}
	m_iCurFrm = pOther.m_iCurFrm;
	m_fAccTime = pOther.m_fAccTime;
	m_bReverse = pOther.m_bReverse;

	m_pAnimator = nullptr;
	m_pImg = pOther.m_pImg;
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
	// �ð� ���� > fDuration -> m_iCurFrm++
	m_fAccTime += fDeltaTime;

	if (m_fAccTime >= m_vecAnimFrm[m_iCurFrm].fDuration)
	{
		// ���� �ð� -> fDuration ��ŭ �ٽ� ���� -> 0���� �ʱ�ȭ���ٴ� ��Ȯ
		m_fAccTime -= m_vecAnimFrm[m_iCurFrm].fDuration;

		m_iCurFrm++;

		if (m_bIsLoop)
		{
			// �ִϸ��̼ǿ� ���� ���������� ó�� ���������� ���ư�
			m_iCurFrm %= m_vecAnimFrm.size();
		}
		else
		{
			if (m_iCurFrm == m_vecAnimFrm.size())
			{
				m_iCurFrm = (int)m_vecAnimFrm.size() - 1;
				m_bIsAnimDone = true;
				m_fAccTime = 0.f;
			}
		}
	}
}

void CAnimation::render()
{
	CGameObject* pObj = m_pAnimator->GetOwnerObj();
	// �׸� ��ġ
	fPoint fptDrawPos = pObj->GetPos();
	// ���� �׷����� �������� �ִϸ��̼�
	tAnimFrm animFrm = m_vecAnimFrm[m_iCurFrm];

	fptDrawPos = fptDrawPos + animFrm.fptOffset;

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(fptDrawPos);
	fPoint fptScale = pObj->GetScale();

	if (animFrm.fptTexScale.x > fptScale.x)
	{
		fptScale.x = animFrm.fptTexScale.x * 2.f;
	}
	if (animFrm.fptTexScale.y > fptScale.y)
	{
		fptScale.y = animFrm.fptTexScale.y * 2.f;
	}

	if (m_bReverse)
	{
		CRenderManager::GetInst()->RenderRevFrame(
			m_pImg,
			fptRenderPos.x - fptScale.x / 2.f,
			fptRenderPos.y - fptScale.y / 2.f,
			fptRenderPos.x + fptScale.x / 2.f,
			fptRenderPos.y + fptScale.y / 2.f,
			animFrm.fptLeftTop.x,
			animFrm.fptLeftTop.y,
			animFrm.fptLeftTop.x + animFrm.fptTexScale.x,
			animFrm.fptLeftTop.y + animFrm.fptTexScale.y
		);
	}
	else
	{
		CRenderManager::GetInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x - fptScale.x / 2.f,
			fptRenderPos.y - fptScale.y / 2.f,
			fptRenderPos.x + fptScale.x / 2.f,
			fptRenderPos.y + fptScale.y / 2.f,
			animFrm.fptLeftTop.x,
			animFrm.fptLeftTop.y,
			animFrm.fptLeftTop.x + animFrm.fptTexScale.x,
			animFrm.fptLeftTop.y + animFrm.fptTexScale.y
		);
	}
}

void CAnimation::Create(CD2DImage* pImg,	// �ִϸ��̼��� �̹���
						fPoint leftTop,		// �ִϸ��̼� ���� ������ �»�� ��ǥ
						fPoint scale,		// �ִϸ��̼� �������� ũ��
						fPoint step,		// �ִϸ��̼� ������ �ݺ� ��ġ
						UINT column,		// ��� �� ����
						float duration,		// �ִϸ��̼� ������ ���� �ð�
						UINT frmCount)		// �ִϸ��̼� ������ ����
{
	m_pImg = pImg;

	tAnimFrm frm = {};
	for (UINT i = 0; i < frmCount; ++i)
	{
		frm.fDuration = duration;	// ���� �ð�
		frm.fptTexScale = scale;	// �ؽ����� ũ��

		UINT count = i;
		if (count != 0 && column != 0 && count % column == 0)
		{
			count = 0;

			leftTop = fPoint(0.f, leftTop.y + scale.y);
		}
		else if (count != 0 && column != 0)
		{
			count %= column;
		}

		// leftTop + ���� ������ �̹��������� �Ÿ� * ���� ������ ī��Ʈ
		frm.fptLeftTop = leftTop + step * count;

		m_vecAnimFrm.push_back(frm);
	}

	m_fCurAnimDuration += duration * frmCount;
}

void CAnimation::SetLoop(bool isLoop)
{
	m_bIsLoop = isLoop;
}

bool CAnimation::GetReverse()
{
	return m_bReverse;
}

float CAnimation::GetAnimDuration()
{
	return m_fCurAnimDuration;
}
