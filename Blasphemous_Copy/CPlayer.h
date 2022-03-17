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

struct PLAYER_ABILITY
{
	float fMaxHp;
	float fCurHp;
	float fMaxMp;
	float fCurMp;

	UINT  iHpPotionCount;
	float fHpRecoveryAmount;

	USHORT  sMoney;
};

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImg;

	PLAYER_STATE m_eCurState;		// 현재 플레이어의 상태
	PLAYER_STATE m_ePrevState;		// 이전 플레이어의 상태

	PLAYER_ATTACK_STATE m_eCurAttState; // 현재 플레이어 어택 상태
	PLAYER_ATTACK_STATE m_ePreAttState; // 이전 플레이어 어택 상태

	PLAYER_ABILITY m_myAbility;

	fVector2D m_fvCurDir;
	fVector2D m_fvPrevDir;

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


	virtual void update() final;
	void update_state();
	void update_move();
	void update_animation();

	virtual void render() final;

	void InitAbility();
	void InitAnimation();

	void Jump();

	const float		 GetVelocity();
	const fVector2D& GetDirVector();

	virtual void OnCollision(CCollider* target) override;
	virtual void OnCollisionEnter(CCollider* target) override;
	virtual void OnCollisionExit(CCollider* target) override;
};

