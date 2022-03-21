#pragma once
class CGameObject;
class CAnimation;
class CD2DImage;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAnim;		// �ִϸ��̼ǵ��� ������ �ִ� �ڷᱸ��
	CAnimation*					m_pCurAnim;		// ���� �׷����� �ִϸ��̼�
	CGameObject*				m_pOwner;

public:
	CAnimator();
	~CAnimator();

	void update();
	void render();

	void CreateAnimation(const wstring& strName, CD2DImage* pImg, fPoint leftTop, fPoint scale,
						fPoint step, UINT column, float duration, UINT frmCount, bool isLoop, bool bReverse);
	CAnimation* FindAnimation(const wstring& strName);
	// �ִϸ��̼� ���
	void Play(const wstring& strName);

	CGameObject* GetOwnerObj();
};

