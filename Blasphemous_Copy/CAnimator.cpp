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
	// 등록되어있던 애니메이션들 지워주기
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

void CAnimator::render(HDC hDC)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(hDC);
}

void CAnimator::CreateAnimation(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint scale, 
								fPoint step, float duration, UINT frmCount, bool isLoop)
{
	CAnimation* pAnim = FindAnimation(strName);

	// 이름이 똑같은 애니메이션을 넣을 때의 반응
	assert(pAnim == nullptr);

	pAnim = new CAnimation;

	pAnim->SetName(strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(pTex, leftTop, scale, step, duration, frmCount);
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

void CAnimator::Play(const wstring& strName)
{
	m_pCurAnim = FindAnimation(strName);
	//m_pCurAnim->InitCurFrm();
}

CGameObject* CAnimator::GetOwnerObj()
{
	return m_pOwner;
}
