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
	fPoint m_fptLookAt;			// ī�޶� ����ų ��ġ
	fPoint m_fptCurLookAt;		// ī�޶� ���� �����ִ� ��ġ
	fPoint m_fptPrevLookAt;		// ī�޶� ������ ���� ��ġ

	CGameObject* m_pTargetObj;	// ������ ���� ������Ʈ
	bool		 m_bFollowX;
	bool		 m_bFollowY;

	fPoint m_fptDiff;			// ���� �����ִ� ��ġ�� �󸶸�ŭ�� ������ �ʿ����� ����
	fPoint m_fptLerpDiff;		// Ÿ�� ��ġ�� ī�޶� �ٶ󺸰��ִ� ��ġ ����

	fPoint m_fptBoundaryLT;		// LeftTop ��� -> �� �̻����� �� �� ����
	fPoint m_fptBoundaryRB;		// RightBottom ��� -> �� �̻����� �� �� ����
	bool   m_bHasBoundary;

	float m_fTime;				// �������� ���󰡴� �ð�
	float m_fAccTime;			// �������� ���󰡴µ� �ҿ�� �ð�
	float m_fSpeed;				// ���������� ���󰡴� �ӷ�
	float m_fPrevSpeed;			// ���������� ���󰡴� �ӷ�
	float m_fAccelGravity;		// �������� ���󰡴� ���ӵ�
	float m_fAccIncrement;		// ���ӵ��� ������

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

	fPoint	GetLookAt();						// ���� ī�޶� ��ġ
	fPoint	GetRenderPos(fPoint objPos);		// ������Ʈ�� �׷������� ��ġ ��ȯ
	fPoint	GetRealPos(fPoint renderPos);		// ���� ���ӻ� ��ǥ ��ȯ
	fPoint	GetLerpPoint();

	void FadeIn(float duration);
	void FadeOut(float duration);

	void LerpDiff(fPoint targetPos);
	void CheckBoundary();
};

