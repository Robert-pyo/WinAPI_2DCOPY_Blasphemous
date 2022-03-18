#pragma once
#include "CGameObject.h"

class CD2DImage;
class CPlayerSword;

enum class PLAYER_STATE
{
	IDLE,
	CROUCH,
	CLIMB,
	RUN,
	ATTACK,
	JUMP,
	JUMPOFF,
	DEAD,
};

enum class PLAYER_ATTACK_STATE
{
	FIRST_SLASH,
	SECOND_SLASH,
	THIRD_SLASH,

	JUMP_SLASH,

	CROUCH_SLASH,
	
	NONE,
};

struct tPlayerAbility
{
	float fMaxHp;
	float fCurHp;
	float fMaxMp;
	float fCurMp;

	UINT  iHpPotionCount;
	float fHpRecoveryAmount;

	float fAtt;

	USHORT  sMoney;
};

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImg;

	PLAYER_STATE m_eCurState;		// ���� �÷��̾��� ����
	PLAYER_STATE m_ePrevState;		// ���� �÷��̾��� ����

	PLAYER_ATTACK_STATE m_eCurAttState; // ���� �÷��̾� ���� ����
	PLAYER_ATTACK_STATE m_ePreAttState; // ���� �÷��̾� ���� ����

	tPlayerAbility m_tAbility;

	fVector2D m_fvCurDir;
	fVector2D m_fvPrevDir;

	float m_fAccTime;
	float m_fVelocity;
	float m_fMaxVelocity;
	float m_fAccelGravity;
	float m_fJumpPower;
	float m_fFrictionValue;
	bool  m_bIsActing;
	bool  m_bIsGrounded;

	float m_fAttackDelay;
	UINT  m_iComboCount;
	bool  m_bIsAttacking;

	CPlayerSword* m_pSword;

public:
	CPlayer();
	virtual ~CPlayer();

	virtual CPlayer* Clone() override;

public:
	virtual void update() final;
	void update_state();
	void update_move();
	void update_animation();

	virtual void render() final;

public:
	void InitAbility();
	void InitAnimation();

public:
	void Jump();

	const float		 GetVelocity();
	const fVector2D& GetDirVector();

	const tPlayerAbility& GetPlayerAbility();

public:
	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
	virtual void OnCollisionExit(CCollider* target) override;
};

