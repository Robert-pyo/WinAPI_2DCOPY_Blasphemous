#pragma once
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,

	NONE,
};

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	fPoint m_fptLookAt;			// 카메라가 가리킬 위치
	fPoint m_fptCurLookAt;		// 카메라가 지금 보고있는 위치
	fPoint m_fptPrevLookAt;		// 카메라가 이전에 보던 위치

	CGameObject* m_pTargetObj;	// 추적할 게임 오브젝트
	bool		 m_bFollowX;
	bool		 m_bFollowY;

	fPoint m_fptDiff;			// 실제 보고있는 위치랑 얼마만큼의 보정이 필요한지 저장
	fPoint m_fptLerpDiff;		// 타겟 위치와 카메라가 바라보고있는 위치 보간

	fPoint m_fptBoundaryLT;		// LeftTop 경계 -> 그 이상으로 갈 수 없음
	fPoint m_fptBoundaryRB;		// RightBottom 경계 -> 그 이상으로 갈 수 없음
	bool   m_bHasBoundary;

	float m_fTime;				// 목적지를 따라가는 시간
	float m_fAccTime;			// 목적지를 따라가는데 소요된 시간
	float m_fSpeed;				// 목적지까지 따라가는 속력
	float m_fPrevSpeed;			// 목적지까지 따라가던 속력
	float m_fAccelGravity;		// 목적지를 따라가는 가속도
	float m_fAccIncrement;		// 가속도의 증감폭

	CAM_EFFECT	m_eEffect;
	CTexture*	m_pImg;
	float		m_fEffectDuration;
	float		m_fCurTime;

	void	CalcDiff();
public:
	void init();
	void update();
	void render();

	void InitCameraPos(fPoint pos);
	void SetLookAt(fPoint lookAt);
	void FollowTargetObj(CGameObject* targetObj, bool flwX, bool flwY);
	void Scroll(fVector2D vec, float velocity);

	void SetBoundary(fPoint leftTop, fPoint rightBtm);
	void SetBoundary(bool hasBoundary);

	fPoint	GetLookAt();						// 현재 카메라 위치
	fPoint	GetRenderPos(fPoint objPos);		// 오브젝트가 그려져야할 위치 반환
	fPoint	GetRealPos(fPoint renderPos);		// 실제 게임상 좌표 반환
	fPoint	GetLerpPoint();

	void FadeIn(float duration);
	void FadeOut(float duration);

	void LerpDiff(fPoint targetPos);
	void CheckBoundary();
};

