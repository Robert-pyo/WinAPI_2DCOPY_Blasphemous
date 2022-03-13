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
	CAnimator*			m_pAnimator;		// 이 애니메이션을 재생할 애니메이터
	wstring				m_strAnimName;		// 애니메이션 이름
	CTexture*			m_pTex;				// 애니메이션을 그릴 텍스쳐
	vector<tAnimFrm>	m_vecAnimFrm;		// 모든 프레임의 자르기 영역 및 유지시간
	int					m_iCurFrm;			// 현재 프레임
	float				m_fAccTime;			// 현재 프레임의 축적 시간
	bool				m_bIsLoop;
	bool				m_bIsDone;

public:
	CAnimation();
	~CAnimation();

	void SetName(const wstring& strName);
	void SetFrame(int frmIndex);
	void SetLoop(bool isLoop);
	void SetAnimDone(bool isDone);

	// 문자열의 경우 문자열의 특성때문에 원본을 반환하기 때문에 const 선언
	const wstring& GetName();
	tAnimFrm& GetFrame(int frmIndex);
	bool GetAnimDone();

	void update();
	void render(HDC hDC);

	// 애니메이션 생성
	void Create(CTexture* pTex, fPoint leftTop, fPoint scale, fPoint step, float duration, UINT frmCount);
};

