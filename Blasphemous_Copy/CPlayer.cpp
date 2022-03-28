#include "framework.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayerSword.h"
#include "CScene.h"
#include "CEnemy.h"
#include "CTile.h"

CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Player", L"texture\\Player\\penitent_anim_merge.png");
	m_pDashImg = CResourceManager::GetInst()->LoadD2DImage(L"Player_Dodge", L"texture\\Player\\Dodge\\penitent_dodge.png");
	InitObject(fPoint(700.f, 0.f), fPoint(134.f, 144.f));
	SetName(L"Player");
	m_fvCurDir		= {1.0f, 0.f};
	m_fvPrevDir		= {};
	m_fVelocity		= 0.f;
	m_fMaxVelocity	= MAX_SPEED;
	m_fAccelGravity	= 0.f;
	m_fFrictionValue = 800.f;
	m_fJumpPower	= -650.f;
	m_bIsGrounded	= false;

	m_fAttackDelay  = 0.2f;
	m_iComboCount	= 0;
	m_bIsAttacking	= false;

	m_fDodgeAccTime = 0.f;
	m_fDodgeDelay = 1.f;
	m_fDodgeDelayAccTime = 0.f;
	m_bIsInvincible = false;

	InitAbility();
	InitAnimation();

	m_eCurState = PLAYER_STATE::IDLE;
	m_eCurAttState = PLAYER_ATTACK_STATE::NONE;

	CreateCollider();
	GetCollider()->SetOffsetPos(fPoint(30.f, 20.f));
	GetCollider()->SetScale(fPoint(36.f, 96.f));

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::FLOOR);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::BUILDING);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::DEFAULT);
}

CPlayer::~CPlayer()
{
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	if (m_eCurState == PLAYER_STATE::DEAD)
	{
		static float fDeathAccTime = 0.f;
		fDeathAccTime += fDeltaTime;

		if (fDeathAccTime > 2.0f)
			DeleteObj(this);
		
		return;
	}

	update_move();
	update_state();
	update_animation();

	CCameraManager::GetInst()->SetLookAt(GetPos());

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_ePreAttState = m_eCurAttState;
	m_fvPrevDir = m_fvCurDir;
}

void CPlayer::update_state()
{
	if (m_fVelocity < 0.1f)
	{
		if (m_fAttackDelay + 0.1f <= m_fAtkAccTime && m_bIsAttacking)
		{
			m_bIsAttacking = false;
			m_eCurAttState = PLAYER_ATTACK_STATE::NONE;
			m_eCurState = PLAYER_STATE::IDLE;
		}

		if (m_eCurState != PLAYER_STATE::JUMP
			&& m_eCurState != PLAYER_STATE::ATTACK)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}

	// 점프 후 땅에 떨어졌을때 A / D 키를 누르고 있을 시 RUN 상태로 전환
	if (PLAYER_STATE::JUMPOFF == m_eCurState)
	{
		if (PRESS_KEY('A') || PRESS_KEY('D'))
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
	}

	// A키 눌렀을 때 RUN 상태
	if (PRESS_KEY('A') && !m_bIsAttacking && m_eCurState != PLAYER_STATE::DODGE)
	{
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
	}

	// D키 눌렀을 때 RUN 상태
	if (PRESS_KEY('D') && !m_bIsAttacking && m_eCurState != PLAYER_STATE::DODGE)
	{
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
	}

	// space바 눌렀을 때 JUMP 상태
	if (PRESS_KEY_DOWN(VK_SPACE) && m_bIsGrounded && !m_bIsAttacking)
	{
		if (m_eCurState == PLAYER_STATE::DODGE)
		{
			InitDodgeState();
		}
		m_eCurState = PLAYER_STATE::JUMP;

		GetAnimator()->FindAnimation(L"Player_Jump_Right")->SetFrame(0);
		GetAnimator()->FindAnimation(L"Player_Jump_Left")->SetFrame(0);
	}

	m_fDodgeDelayAccTime += fDeltaTime;
	if (PRESS_KEY_DOWN(VK_LSHIFT) && m_bIsGrounded && !m_bIsAttacking && m_fDodgeDelay <= m_fDodgeDelayAccTime)
	{
		if (m_eCurState != PLAYER_STATE::DODGE)
		{
			GetAnimator()->FindAnimation(L"Player_Dodge_Right")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Player_Dodge_Left")->SetFrame(0);
			GetCollider()->SetScale(fPoint(GetCollider()->GetScale().x * 2.f, GetCollider()->GetScale().y / 2.f));
			GetCollider()->SetOffsetPos(fPoint(GetCollider()->GetOffsetPos().x, GetCollider()->GetOffsetPos().y * 2.f));
		}

		m_eCurState = PLAYER_STATE::DODGE;
	}
	if (m_eCurState == PLAYER_STATE::DODGE)
	{
		m_fDodgeAccTime += fDeltaTime;
		m_bIsInvincible = true;
		if (m_fDodgeAccTime >= GetAnimator()->FindAnimation(L"Player_Dodge_Right")->GetAnimDuration())
		{
			m_eCurState = PLAYER_STATE::IDLE;
			InitDodgeState();
		}
	}

	m_fAtkAccTime += fDeltaTime;
	// K 입력 시 공격
	if (PRESS_KEY_DOWN('K') && m_fAttackDelay <= m_fAtkAccTime
		&& m_eCurState != PLAYER_STATE::CLIMB)
	{
		if (m_eCurState == PLAYER_STATE::DODGE)
			InitDodgeState();

		m_eCurState = PLAYER_STATE::ATTACK;

		m_bIsAttacking = true;
		m_fVelocity = 0.f;

		// 너무 늦게 입력했다면 콤보 초기화
		if (m_fAttackDelay + 0.3f <= m_fAtkAccTime)
		{
			m_iComboCount = 0;
			m_fAttackDelay = GetAnimator()->FindAnimation(L"Player_Attack_Combo1_R")->GetAnimDuration();
		}

		if (m_iComboCount == 3)
		{
			m_iComboCount %= 3;
			m_fAttackDelay = GetAnimator()->FindAnimation(L"Player_Attack_Combo1_R")->GetAnimDuration();
		}

		if (m_iComboCount == 0)
		{
			m_fAtkAccTime = 0;
			m_eCurAttState = PLAYER_ATTACK_STATE::FIRST_SLASH;
			GetAnimator()->FindAnimation(L"Player_Attack_Combo1_R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Player_Attack_Combo1_L")->SetFrame(0);
			m_pSword->Attack();
		}
		else if (m_iComboCount == 1)
		{
			m_fAtkAccTime = 0;
			m_eCurAttState = PLAYER_ATTACK_STATE::SECOND_SLASH;
			GetAnimator()->FindAnimation(L"Player_Attack_Combo2_R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Player_Attack_Combo2_L")->SetFrame(0);
			m_pSword->Attack();
		}
		else if (m_iComboCount == 2)
		{
			m_fAtkAccTime = 0;
			m_eCurAttState = PLAYER_ATTACK_STATE::THIRD_SLASH;
			GetAnimator()->FindAnimation(L"Player_Attack_Combo3_R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Player_Attack_Combo3_L")->SetFrame(0);
			m_pSword->Attack();
			m_fAttackDelay = GetAnimator()->FindAnimation(L"Player_Attack_Combo3_R")->GetAnimDuration();
		}
	}
}

void CPlayer::update_move()
{
	if (PRESS_KEY('A') && !m_bIsAttacking)
	{
		if (m_fVelocity < 250.f)
			m_fVelocity += 100.f;

		if (!PRESS_KEY('D') && m_eCurState != PLAYER_STATE::DODGE)
		{
			m_fvCurDir.x = -1;
		}

		m_fVelocity += 1000.f * fDeltaTime;
	}
	
	if (PRESS_KEY('D') && !m_bIsAttacking)
	{
		if (m_fVelocity < 250.f)
			m_fVelocity += 100.f;

		if (!PRESS_KEY('A') && m_eCurState != PLAYER_STATE::DODGE)
		{
			m_fvCurDir.x = 1;
		}

		m_fVelocity += 1000.f * fDeltaTime;
	}

	if (m_eCurState == PLAYER_STATE::JUMP && m_bIsGrounded)
	{
		Jump();
	}

	if (m_eCurState == PLAYER_STATE::DODGE)
	{
		Dodge();
	}

	// 마찰력
	float fFriction = m_fvCurDir.x * (-1) * m_fFrictionValue * fDeltaTime;

	if (m_fvCurDir.x > 0.f)
	{
		if (m_fVelocity <= abs(fFriction))
		{
			m_fVelocity = 0.f;
		}
		else
		{
			m_fVelocity += fFriction;
		}
	}
	else
	{
		if (m_fVelocity <= fFriction)
		{
			m_fVelocity = 0.f;
		}
		else
		{
			m_fVelocity -= fFriction;
		}
	}
	fPoint fptPos = GetPos();

	fptPos.x += m_fvCurDir.x * m_fVelocity * fDeltaTime;
	fptPos.y += m_fAccelGravity * fDeltaTime;

	SetPos(fptPos);

	m_fAccelGravity += GRAVITY * fDeltaTime;
	if (m_fAccelGravity >= 1000.f)
		m_fAccelGravity = 1000.f;
	if (m_fVelocity >= m_fMaxVelocity)
		m_fVelocity = m_fMaxVelocity;

}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_fvPrevDir == m_fvCurDir && m_ePreAttState == m_eCurAttState)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Idle_Left");
		}
		else
		{
			GetAnimator()->Play(L"Player_Idle_Right");
		}
	}break;

	case PLAYER_STATE::RUN:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Running_Left");
		}
		else
		{
			GetAnimator()->Play(L"Player_Running_Right");
		}
	}break;

	case PLAYER_STATE::JUMP:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Jump_Left");
		}
		else
		{
			GetAnimator()->Play(L"Player_Jump_Right");
		}
	}break;
	case PLAYER_STATE::JUMPOFF:
	{
		static float fTime = 0.f;
		fTime += fDeltaTime;
		if (GetAnimator()->FindAnimation(L"Player_Jumpoff_Right")->GetAnimDuration() <= fTime)
		{
			m_eCurState = PLAYER_STATE::IDLE;
			fTime = 0.f;
		}

		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Jumpoff_Left");
		}
		else
		{
			GetAnimator()->Play(L"Player_Jumpoff_Right");
		}
	}break;

	case PLAYER_STATE::ATTACK:
	{
		if (-1 == m_fvCurDir.x)
		{
			switch (m_eCurAttState)
			{
			case PLAYER_ATTACK_STATE::FIRST_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo1_L");
				break;
			case PLAYER_ATTACK_STATE::SECOND_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo2_L");
				break;
			case PLAYER_ATTACK_STATE::THIRD_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo3_L");
				break;
			}
		}
		else
		{
			switch (m_eCurAttState)
			{
			case PLAYER_ATTACK_STATE::FIRST_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo1_R");
				break;
			case PLAYER_ATTACK_STATE::SECOND_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo2_R");
				break;
			case PLAYER_ATTACK_STATE::THIRD_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo3_R");
				break;
			}
		}
	}break;

	case PLAYER_STATE::DODGE:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Dodge_Left");
		}
		else
		{
			GetAnimator()->Play(L"Player_Dodge_Right");
		}
	}break;

	case PLAYER_STATE::HIT:
	{
		if (-1 == m_fvCurDir.x)
		{
			//GetAnimator()->Play(L"");
		}
		else
		{
			//GetAnimator()->Play(L"");
		}
	}break;
	}
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::component_render()
{
	CGameObject::component_render();
	if (CSceneManager::GetInst()->GetIsDebugging())
	{
		debug_render();
	}
}

void CPlayer::debug_render()
{
	CGameObject::debug_render();

	wstring strCurState = L"";

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
		strCurState = L"Idle";
		break;
	case PLAYER_STATE::CROUCH:
		strCurState = L"Crouch";
		break;
	case PLAYER_STATE::CLIMB:
		strCurState = L"Climb";
		break;
	case PLAYER_STATE::RUN:
		strCurState = L"Run";
		break;
	case PLAYER_STATE::DODGE:
		strCurState = L"Dodge";
		break;
	case PLAYER_STATE::ATTACK:
		strCurState = L"Attack";
		break;
	case PLAYER_STATE::JUMP:
		strCurState = L"Jump";
		break;
	case PLAYER_STATE::DEAD:
		strCurState = L"Dead";
		break;
	default:
		strCurState = L"None";
		break;
	}

	fPoint fptRenderPos = CCameraManager::GetInst()->GetRenderPos(GetCollider()->GetFinalPos());

	// TODO : 이 부분에서 자꾸 메모리 누수 발생하는데 어디서 렌더 텍스트에 발생할만한 곳이 어딘지를 모르겠음
	// 분명 다 release 해줬는데..
	CRenderManager::GetInst()->RenderText(strCurState,
		fptRenderPos.x - GetScale().x * 2.f,
		fptRenderPos.y - GetScale().y / 1.5f,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y,
		13, RGB(0, 255, 0));

	wstring strInv = L"Inv : ";
	if (m_bIsInvincible)
	{
		strInv += L"True";
	}
	else
	{
		strInv += L"False";
	}

	CRenderManager::GetInst()->RenderText(strInv,
		fptRenderPos.x - GetScale().x * 2.f,
		fptRenderPos.y,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y,
		13, RGB(0, 255, 0));

	static WCHAR hp[5];
	swprintf_s(hp, L"%4d", (int)m_tAbility.fCurHp);
	wstring strHp = L"Current HP : ";
	strHp += hp;
	CRenderManager::GetInst()->RenderText(strHp,
		fptRenderPos.x - GetScale().x,
		fptRenderPos.y + GetScale().y / 1.5f,
		fptRenderPos.x + GetScale().x,
		fptRenderPos.y,
		15, RGB(0, 255, 0));
}


void CPlayer::Jump()
{
	m_bIsGrounded = false;
	m_fAccelGravity += m_fJumpPower;
}

void CPlayer::Dodge()
{
	m_fMaxVelocity = 500.f;
	m_fVelocity = 500.f;
}

void CPlayer::InitDodgeState()
{
	m_bIsInvincible = false;
	m_fDodgeAccTime = 0.f;
	m_fDodgeDelayAccTime = 0.f;
	m_fMaxVelocity = MAX_SPEED;
	GetCollider()->SetScale(fPoint(GetCollider()->GetScale().x / 2.f, GetCollider()->GetScale().y * 2.f));
	GetCollider()->SetOffsetPos(fPoint(GetCollider()->GetOffsetPos().x, GetCollider()->GetOffsetPos().y / 2.f));
}

void CPlayer::Hit(CGameObject* other)
{
	if (m_eCurState == PLAYER_STATE::DEAD) return;

	CEnemy* pEnemy = (CEnemy*)other;

	m_tAbility.fCurHp -= pEnemy->GetEnemyInfo().fAtt;

	m_eCurState = PLAYER_STATE::HIT;
	
	if (m_tAbility.fCurHp <= 0)
	{
		Die();
	}
}

void CPlayer::Die()
{
	m_eCurState = PLAYER_STATE::DEAD;
	m_eCurAttState = PLAYER_ATTACK_STATE::NONE;

	CCameraManager::GetInst()->FadeOut(2.0f);
}

const float CPlayer::GetVelocity()
{
	return m_fVelocity;
}

const fVector2D& CPlayer::GetDirVector()
{
	return m_fvCurDir;
}

const tPlayerAbility& CPlayer::GetPlayerAbility()
{
	return m_tAbility;
}

void CPlayer::SetPlayerAbility(const tPlayerAbility& tAbility)
{
	m_tAbility = tAbility;
}

void CPlayer::InitAbility()
{
	CPlayerSword* pSword = new CPlayerSword;
	pSword->SetOwnerObj(this);
	m_pSword = pSword;

	m_tAbility.fMaxHp = 100.f;
	m_tAbility.fCurHp = 100.f;
	m_tAbility.fMaxMp = 100.f;
	m_tAbility.fCurMp = 100.f;

	m_tAbility.sMaxPotionCount = 2;
	m_tAbility.sHpPotionCount = 2;

	m_tAbility.fHpRecoveryAmount = m_tAbility.fMaxHp / 2.f;

	m_tAbility.fAtt = m_pSword->GetAttValue();

	m_tAbility.sMoney = 0;
}

void CPlayer::InitAnimation()
{
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Player_Idle_Right", m_pImg, fPoint(0.f, 0.f), fPoint(71.f, 77.f), fPoint(71.f, 0.f), 0, 0.1f, 13, true, false);
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pImg, fPoint(29.f, 77.f), fPoint(71.f, 77.f), fPoint(71.f, 0.f), 0, 0.1f, 13, true, false);
	GetAnimator()->CreateAnimation(L"Player_Running_Right", m_pImg, fPoint(0.f, 155.f), fPoint(77.f, 77.f), fPoint(78.f, 0.f), 0, 0.045f, 14, true, false);
	GetAnimator()->CreateAnimation(L"Player_Running_Left", m_pImg, fPoint(19.f, 236.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0, 0.045f, 14, true, false);
	GetAnimator()->CreateAnimation(L"Player_Jump_Right", m_pImg, fPoint(7.f, 473.f), fPoint(81.f, 81.f), fPoint(81.f, 0.f), 0, 0.05f, 6, false, false);
	GetAnimator()->CreateAnimation(L"Player_Jump_Left", m_pImg, fPoint(7.f, 473.f), fPoint(81.f, 81.f), fPoint(81.f, 0.f), 0, 0.05f, 6, false, true);
	GetAnimator()->CreateAnimation(L"Player_Jumpoff_Right", m_pImg, fPoint(504.f, 472.f), fPoint(82.f, 72.f), fPoint(82.f, 0.f), 0, 0.05f, 3, false, false);
	GetAnimator()->CreateAnimation(L"Player_Jumpoff_Left", m_pImg, fPoint(504.f, 472.f), fPoint(82.f, 72.f), fPoint(82.f, 0.f), 0, 0.05f, 3, false, true);

	GetAnimator()->CreateAnimation(L"Player_Attack_Combo1_R", m_pImg, fPoint(0.f, 560.f), fPoint(163.f, 75.f), fPoint(0.f, 75.f), 0, 0.04f, 7, false, false);
	GetAnimator()->CreateAnimation(L"Player_Attack_Combo1_L", m_pImg, fPoint(0.f, 560.f), fPoint(163.f, 75.f), fPoint(0.f, 75.f), 0, 0.04f, 7, false, true);
	GetAnimator()->CreateAnimation(L"Player_Attack_Combo2_R", m_pImg, fPoint(163.f, 560.f), fPoint(163.f, 75.f), fPoint(0.f, 75.f), 0, 0.04f, 7, false, false);
	GetAnimator()->CreateAnimation(L"Player_Attack_Combo2_L", m_pImg, fPoint(163.f, 560.f), fPoint(163.f, 75.f), fPoint(0.f, 75.f), 0, 0.04f, 7, false, true);
	GetAnimator()->CreateAnimation(L"Player_Attack_Combo3_R", m_pImg, fPoint(326.f, 560.f), fPoint(163.f, 75.f), fPoint(0.f, 75.f), 0, 0.04f, 14, false, false);
	GetAnimator()->CreateAnimation(L"Player_Attack_Combo3_L", m_pImg, fPoint(326.f, 560.f), fPoint(163.f, 75.f), fPoint(0.f, 75.f), 0, 0.04f, 14, false, true);

	GetAnimator()->CreateAnimation(L"Player_Dodge_Right", m_pDashImg, fPoint(0.f, 0.f), fPoint(97.f, 72.f), fPoint(97.f, 0.f), 4, 0.03f, 24, false, false);
	GetAnimator()->CreateAnimation(L"Player_Dodge_Left", m_pDashImg, fPoint(0.f, 0.f), fPoint(97.f, 72.f), fPoint(97.f, 0.f), 4, 0.03f, 24, false, true);

#pragma region AnimationFrameEdit
	CAnimation* pAnim;
	pAnim = GetAnimator()->FindAnimation(L"Player_Idle_Left");
	for (int i = 0; i < 13; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 53.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Running_Left");
	for (int i = 0; i < 14; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 60.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Jump_Right");
	pAnim->GetFrame(3).fDuration += 0.05f;
	pAnim->GetFrame(4).fDuration += 0.05f;
	for (int i = 0; i < 6; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 25.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Jump_Left");
	pAnim->GetFrame(3).fDuration += 0.05f;
	pAnim->GetFrame(4).fDuration += 0.05f;
	for (int i = 0; i < 6; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 35.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Jumpoff_Right");
	pAnim->GetFrame(0).fDuration += 0.15f;
	pAnim->GetFrame(1).fDuration += 0.05f;
	for (int i = 0; i < 3; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 20.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Jumpoff_Left");
	pAnim->GetFrame(0).fDuration += 0.15f;
	pAnim->GetFrame(1).fDuration += 0.05f;
	for (int i = 0; i < 3; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 40.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Attack_Combo1_R");
	for (int i = 0; i < 7; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 100.f;
	}
	pAnim = GetAnimator()->FindAnimation(L"Player_Attack_Combo1_L");
	for (int i = 0; i < 7; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 30.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Attack_Combo2_R");
	for (int i = 0; i < 7; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 100.f;
	}
	pAnim = GetAnimator()->FindAnimation(L"Player_Attack_Combo2_L");
	for (int i = 0; i < 7; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 30.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Attack_Combo3_R");
	for (int i = 0; i < 14; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 100.f;
	}
	pAnim->GetFrame(2).fDuration = 0.1f;
	pAnim->GetFrame(3).fDuration = 0.1f;
	pAnim->GetFrame(4).fDuration = 0.1f;

	pAnim = GetAnimator()->FindAnimation(L"Player_Attack_Combo3_L");
	for (int i = 0; i < 14; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x -= 40.f;
	}
	pAnim->GetFrame(2).fDuration = 0.1f;
	pAnim->GetFrame(3).fDuration = 0.1f;
	pAnim->GetFrame(4).fDuration = 0.1f;

	GetAnimator()->Play(L"Player_Idle_Right");

	pAnim = GetAnimator()->FindAnimation(L"Player_Dodge_Left");
	for (int i = 0; i < 24; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 30.f;
	}
#pragma endregion
}

#pragma region CollisionCheck
void CPlayer::OnCollision(CCollider* target)
{
	if (GROUP_GAMEOBJ::TILE == target->GetOwnerObj()->GetObjGroup() || 
		GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup())
	{
		fVector2D fvDiff = CCollisionManager::GetInst()->GetColliderDiff(GetCollider(), target);

		CTile* pTile = (CTile*)target->GetOwnerObj();

		// 플레이어 바닥 및 벽 충돌 처리

		// 왼쪽 벽
		if (m_fvCurDir.x < 0.f && 
			(pTile->GetGroup() == GROUP_TILE::WALL || pTile->GetGroup() == GROUP_TILE::GROUND))
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				// 플레이어가 벽보다 오른쪽에 있을 때
				if (fvDiff.y > fvDiff.x && GetCollider()->GetBorderPos().right > target->GetBorderPos().right)
				{
					fPoint fptPos = GetPos();
					fptPos.x += m_fVelocity * fDeltaTime;
					SetPos(fptPos);
				}
			}
		}
		// 오른쪽 벽
		if (m_fvCurDir.x > 0.f &&
			(pTile->GetGroup() == GROUP_TILE::WALL || pTile->GetGroup() == GROUP_TILE::GROUND))
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				// 플레이어가 벽보다 왼쪽에 있을 때
				if (fvDiff.y > fvDiff.x && GetCollider()->GetBorderPos().left < target->GetBorderPos().left)
				{
					fPoint fptPos = GetPos();
					fptPos.x -= m_fVelocity * fDeltaTime;
					SetPos(fptPos);
				}
			}
		}

		if (m_fAccelGravity > 0.f)
		{
			if (pTile->GetGroup() == GROUP_TILE::GROUND || GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup())
			{
				// 위쪽
				if (GetCollider()->GetBorderPos().bottom > target->GetBorderPos().bottom &&
					GetCollider()->GetBorderPos().top <= target->GetBorderPos().bottom)
				{
					if (fvDiff.y < fvDiff.x)
					{
						fPoint fptPos = GetPos();
						// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
						fptPos.y += fvDiff.y;
						SetPos(fptPos);
					}
				}

				// 아래쪽
				if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
					&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
				{
					if (fvDiff.y < fvDiff.x)
					{
						fPoint fptPos = GetPos();
						// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
						fptPos.y -= fvDiff.y;
						SetPos(fptPos);
						m_fAccelGravity = 0.f;
					}
				}
			}

			if (pTile->GetGroup() == GROUP_TILE::PLATFORM)
			{
				// 아래쪽
				if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
					&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
				{
					if (fvDiff.y < fvDiff.x)
					{
						fPoint fptPos = GetPos();
						// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
						fptPos.y -= fvDiff.y;
						SetPos(fptPos);
						m_fAccelGravity = 0.f;
					}
				}
			}
		}
	}
}

void CPlayer::OnCollisionEnter(CCollider* target)
{
	if (m_fAccelGravity > 0.f)
	{
		if (GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup()
			|| GROUP_GAMEOBJ::TILE == target->GetOwnerObj()->GetObjGroup())
		{
			fVector2D fvDiff = CCollisionManager::GetInst()->GetColliderDiff(GetCollider(), target);

			if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
			{
				if (fvDiff.y < fvDiff.x)
				{
					m_bIsGrounded = true;

					if (m_eCurState == PLAYER_STATE::JUMP)
					{
						GetAnimator()->FindAnimation(L"Player_Jumpoff_Right")->SetFrame(0);
						GetAnimator()->FindAnimation(L"Player_Jumpoff_Left")->SetFrame(0);

						m_eCurState = PLAYER_STATE::JUMPOFF;
					}
				}
			}
		}
	}
}

void CPlayer::OnCollisionExit(CCollider* target)
{
}
#pragma endregion