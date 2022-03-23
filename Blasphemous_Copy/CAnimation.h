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
	CAnimator*			m_pAnimator;		// 이 애니메이션을 재생할 애니메이터
	wstring				m_strAnimName;		// 애니메이션 이름
	CD2DImage*			m_pImg;				// 애니메이션 이미지
	vector<tAnimFrm>	m_vecAnimFrm;		// 모든 프레임의 자르기 영역 및 유지시간
	int					m_iCurFrm;			// 현재 프레임
	float				m_fAccTime;			// 현재 프레임의 축적 시간
	float				m_fCurAnimDuration;	// 현재 플레이 중인 애니메이션의 총 유지 시간
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

	// 문자열의 경우 문자열의 특성때문에 원본을 반환하기 때문에 const 선언
	const wstring& GetName();
	tAnimFrm& GetFrame(int frmIndex);
	bool  GetReverse();
	float GetAnimDuration();

	void update();
	void render();

	// 애니메이션 생성
	void Create(CD2DImage* pImg, fPoint leftTop, fPoint scale, fPoint step, UINT column, float duration, UINT frmCount);

public:
	bool IsAnimDone() { return m_bIsAnimDone; }

private:
	void SetAnimDone(bool bIsDone) { m_bIsAnimDone = bIsDone; }
};

