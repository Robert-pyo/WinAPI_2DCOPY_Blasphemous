#pragma once
class CAnimator;
class CD2DImage;

struct tAnimFrm
{
	fPoint	fptLeftTop;
	fPoint	fptTexScale;
	fPoint	fptOffset;
	float	fDuration;
};

class CAnimation
{
	friend class CAnimator;

private:
	CAnimator*			m_pAnimator;		// �� �ִϸ��̼��� ����� �ִϸ�����
	wstring				m_strAnimName;		// �ִϸ��̼� �̸�
	CD2DImage*			m_pImg;				// �ִϸ��̼� �̹���
	vector<tAnimFrm>	m_vecAnimFrm;		// ��� �������� �ڸ��� ���� �� �����ð�
	int					m_iCurFrm;			// ���� ������
	float				m_fAccTime;			// ���� �������� ���� �ð�
	float				m_fCurAnimDuration;	// ���� �÷��� ���� �ִϸ��̼��� �� ���� �ð�
	bool				m_bIsLoop;
	bool				m_bReverse;
	bool				m_bIsAnimDone;

public:
	CAnimation();
	CAnimation(const CAnimation& pOther);
	~CAnimation();

public:
	void SetName(const wstring& strName);
	void SetFrame(int frmIndex);
	void SetLoop(bool isLoop);

	// ���ڿ��� ��� ���ڿ��� Ư�������� ������ ��ȯ�ϱ� ������ const ����
	const wstring& GetName();
	tAnimFrm& GetFrame(int frmIndex);
	bool  GetReverse();
	float GetAnimDuration();

	void update();
	void render();

	// �ִϸ��̼� ����
	void Create(CD2DImage* pImg, fPoint leftTop, fPoint scale, fPoint step, UINT column, float duration, UINT frmCount);

public:
	bool IsAnimDone() { return m_bIsAnimDone; }

private:
	void SetAnimDone(bool bIsDone) { m_bIsAnimDone = bIsDone; }
};

