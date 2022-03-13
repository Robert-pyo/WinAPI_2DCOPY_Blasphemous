#pragma once
class CGameObject;
class CAnimation;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAnim;		// 애니메이션들을 가지고 있는 자료구조
	CAnimation*					m_pCurAnim;		// 현재 그려야할 애니메이션
	CGameObject*				m_pOwner;

public:
	CAnimator();
	~CAnimator();

	void update();
	void render(HDC hDC);

	void CreateAnimation(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint scale, 
						fPoint step, float duration, UINT frmCount, bool isLoop);
	CAnimation* FindAnimation(const wstring& strName);
	// 애니메이션 재생
	void Play(const wstring& strName);

	CGameObject* GetOwnerObj();
};

