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
				m_bIsDone = true;
			}
		}
	}
}

void CAnimation::render(HDC hDC)
{
	CGameObject* pObj = m_pAnimator->GetOwnerObj();
	// �׸� ��ġ
	fPoint fptDrawPos = pObj->GetPos();
	// ���� �׷����� �������� �ִϸ��̼�
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

void CAnimation::Create(CTexture* pTex,		// �ִϸ��̼��� �̹���
						fPoint leftTop,		// �ִϸ��̼� ���� ������ �»�� ��ǥ
						fPoint scale,		// �ִϸ��̼� �������� ũ��
						fPoint step,		// �ִϸ��̼� ������ �ݺ� ��ġ
						float duration,		// �ִϸ��̼� ������ ���� �ð�
						UINT frmCount)		// �ִϸ��̼� ������ ����
{
	m_pTex = pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < frmCount; ++i)
	{
		frm.fDuration = duration;	// ���� �ð�
		frm.fptTexScale = scale;	// �ؽ����� ũ��
		// leftTop + ���� ������ �̹��������� �Ÿ� * ���� ������ ī��Ʈ
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