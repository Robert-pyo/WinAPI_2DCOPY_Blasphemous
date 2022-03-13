#pragma once
class CAnimator;
class CTexture;

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
	CTexture*			m_pTex;				// �ִϸ��̼��� �׸� �ؽ���
	vector<tAnimFrm>	m_vecAnimFrm;		// ��� �������� �ڸ��� ���� �� �����ð�
	int					m_iCurFrm;			// ���� ������
	float				m_fAccTime;			// ���� �������� ���� �ð�
	bool				m_bIsLoop;
	bool				m_bIsDone;

public:
	CAnimation();
	~CAnimation();

	void SetName(const wstring& strName);
	void SetFrame(int frmIndex);
	void SetLoop(bool isLoop);
	void SetAnimDone(bool isDone);

	// ���ڿ��� ��� ���ڿ��� Ư�������� ������ ��ȯ�ϱ� ������ const ����
	const wstring& GetName();
	tAnimFrm& GetFrame(int frmIndex);
	bool GetAnimDone();

	void update();
	void render(HDC hDC);

	// �ִϸ��̼� ����
	void Create(CTexture* pTex, fPoint leftTop, fPoint scale, fPoint step, float duration, UINT frmCount);
};

