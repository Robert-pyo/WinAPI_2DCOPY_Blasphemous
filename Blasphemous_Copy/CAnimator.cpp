#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pOwner	= nullptr;
	m_pCurAnim	= nullptr;
}

CAnimator::~CAnimator()
{
	// ��ϵǾ��ִ� �ִϸ��̼ǵ� �����ֱ�
	for (map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin(); iter != m_mapAnim.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapAnim.clear();
}

void CAnimator::update()
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->update();
}

void CAnimator::render()
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render();
}

void CAnimator::CreateAnimation(const wstring& strName, CD2DImage* pImg, fPoint leftTop, fPoint scale,
								fPoint step, float duration, UINT frmCount, bool isLoop)
{
	CAnimation* pAnim = FindAnimation(strName);

	// �̸��� �Ȱ��� �ִϸ��̼��� ���� ���� ����
	assert(pAnim == nullptr);

	pAnim = new CAnimation;

	pAnim->SetName(strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(pImg, leftTop, scale, step, duration, frmCount);
	pAnim->SetLoop(isLoop);

	m_mapAnim.insert(make_pair(strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& strName, bool bReverse)
{
	m_pCurAnim = FindAnimation(strName);
	m_pCurAnim->m_bReverse = bReverse;
}

CGameObject* CAnimator::GetOwnerObj()
{
	return m_pOwner;
}
