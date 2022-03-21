#include "framework.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayerSword.h"
#include "CScene.h"

CPlayer::CPlayer()
{
	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Player", L"\\texture\\Player\\penitent_anim_merge.png");
	InitObject(fPoint(700.f, 0.f), fPoint(134.f, 144.f));
	SetName(L"Player");
	m_fvCurDir		= {1.0f, 0.f};
	m_fvPrevDir		= {};
	m_fVelocity		= 0.f;
	m_fMaxVelocity	= 300.f;
	m_fAccelGravity	= 0.f;
	m_fFrictionValue = 1000.f;
	m_fJumpPower	= -650.f;
	m_bIsGrounded	= false;

	m_pSword		= new CPlayerSword;
	m_pSword->SetOwnerObj(this);
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	pCurScene->AddObject(m_pSword, GROUP_GAMEOBJ::WEAPON);

	m_fAttackDelay  = 0.2f;
	m_iComboCount	= 0;
	m_bIsAttacking	= false;

	m_eCurState = PLAYER_STATE::IDLE;
	m_eCurAttState = PLAYER_ATTACK_STATE::NONE;

	CreateAnimator();

	CreateCollider();
	GetCollider()->SetOffsetPos(fPoint(30.f, 20.f));
	GetCollider()->SetScale(fPoint(36.f, 96.f));
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
	if (PRESS_KEY(VK_LBUTTON))
	{
		fPoint mousePos = CCameraManager::GetInst()->GetRealPos(MousePos());
		m_fAccelGravity = 0.f;
		SetPos(mousePos);
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
	if (m_fVelocity == 0.f)
	{
		if (m_fAttackDelay + 0.1f < m_fAccTime && m_bIsAttacking)
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
	if (PRESS_KEY('A') && !m_bIsAttacking)
	{
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
	}

	// D키 눌렀을 때 RUN 상태
	if (PRESS_KEY('D') && !m_bIsAttacking)
	{
		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::RUN;
		}
	}

	// space바 눌렀을 때 JUMP 상태
	if (PRESS_KEY_DOWN(VK_SPACE) && !m_bIsAttacking)
	{
		m_eCurState = PLAYER_STATE::JUMP;

		GetAnimator()->FindAnimation(L"Player_Jump_Right")->SetFrame(0);
		GetAnimator()->FindAnimation(L"Player_Jump_Left")->SetFrame(0);
	}

	m_fAccTime += fDeltaTime;
	// K 입력 시 공격
	if (PRESS_KEY_DOWN('K') && m_fAttackDelay <= m_fAccTime && m_eCurState != PLAYER_STATE::CLIMB)
	{
		m_eCurState = PLAYER_STATE::ATTACK;

		m_bIsAttacking = true;
		m_fVelocity = 0.f;

		// 너무 늦게 입력했다면 콤보 초기화
		if (m_fAttackDelay + 0.3f <= m_fAccTime)
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
			m_fAccTime = 0;
			m_eCurAttState = PLAYER_ATTACK_STATE::FIRST_SLASH;
			GetAnimator()->FindAnimation(L"Player_Attack_Combo1_R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Player_Attack_Combo1_L")->SetFrame(0);
			m_pSword->Attack();
		}
		else if (m_iComboCount == 1)
		{
			m_fAccTime = 0;
			m_eCurAttState = PLAYER_ATTACK_STATE::SECOND_SLASH;
			GetAnimator()->FindAnimation(L"Player_Attack_Combo2_R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"Player_Attack_Combo2_L")->SetFrame(0);
			m_pSword->Attack();
		}
		else if (m_iComboCount == 2)
		{
			m_fAccTime = 0;
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
	if (PRESS_KEY_DOWN('A') && !m_bIsAttacking)
		m_fVelocity += 50.f;
	if (PRESS_KEY('A') && !m_bIsAttacking)
	{
		if (!PRESS_KEY('D'))
		{
			m_fvCurDir.x = -1;
		}

		m_fVelocity += 2000.f * fDeltaTime;
		if (PRESS_KEY('D'))
		{
			m_fVelocity -= 3000.f * fDeltaTime;
		}
	}
	
	if (PRESS_KEY_DOWN('D') && !m_bIsAttacking)
		m_fVelocity += 50.f;
	if (PRESS_KEY('D') && !m_bIsAttacking)
	{
		if (!PRESS_KEY('A'))
		{
			m_fvCurDir.x = 1;
		}
		m_fVelocity += 2000.f * fDeltaTime;
		if (PRESS_KEY('A'))
		{
			m_fVelocity -= 3000.f * fDeltaTime;
		}
	}

	if (PRESS_KEY_DOWN(VK_SPACE) && m_bIsGrounded && !m_bIsAttacking)
	{
		Jump();
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
			Logger::debug(L"IDLE_LEFT");
		}
		else
		{
			GetAnimator()->Play(L"Player_Idle_Right");
			Logger::debug(L"IDLE_RIGHT");
		}
	}break;

	case PLAYER_STATE::RUN:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Running_Left");
			Logger::debug(L"RUN_LEFT");
		}
		else
		{
			GetAnimator()->Play(L"Player_Running_Right");
			Logger::debug(L"RUN_RIGHT");
		}
	}break;

	case PLAYER_STATE::JUMP:
	{
		if (-1 == m_fvCurDir.x)
		{
			GetAnimator()->Play(L"Player_Jump_Left");
			Logger::debug(L"JUMP_LEFT");
		}
		else
		{
			GetAnimator()->Play(L"Player_Jump_Right");
			Logger::debug(L"JUMP_RIGHT");
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
			Logger::debug(L"JUMPOFF_LEFT");
		}
		else
		{
			GetAnimator()->Play(L"Player_Jumpoff_Right");
			Logger::debug(L"JUMPOFF_RIGHT");
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
				Logger::debug(L"Combo1");
				break;
			case PLAYER_ATTACK_STATE::SECOND_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo2_L");
				Logger::debug(L"Combo2");
				break;
			case PLAYER_ATTACK_STATE::THIRD_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo3_L");
				Logger::debug(L"Combo3");
				break;
			}
		}
		else
		{
			switch (m_eCurAttState)
			{
			case PLAYER_ATTACK_STATE::FIRST_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo1_R");
				Logger::debug(L"Combo1");
				break;
			case PLAYER_ATTACK_STATE::SECOND_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo2_R");
				Logger::debug(L"Combo2");
				break;
			case PLAYER_ATTACK_STATE::THIRD_SLASH:
				GetAnimator()->Play(L"Player_Attack_Combo3_R");
				Logger::debug(L"Combo3");
				break;
			}
		}
	}break;
	}
}

void CPlayer::render()
{
	component_render();
}


void CPlayer::Jump()
{
	m_bIsGrounded = false;
	m_fAccelGravity += m_fJumpPower;
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

void CPlayer::SetPlayerAbility(tPlayerAbility tAbility)
{
	m_tAbility = tAbility;
}

void CPlayer::InitAbility()
{
	m_tAbility.fMaxHp = 100.f;
	m_tAbility.fCurHp = 100.f;
	m_tAbility.fMaxMp = 100.f;
	m_tAbility.fCurMp = 100.f;

	m_tAbility.iHpPotionCount = 2;
	m_tAbility.fHpRecoveryAmount = m_tAbility.fMaxHp / 2.f;

	m_tAbility.fAtt = m_pSword->GetAttValue();

	m_tAbility.sMoney = 0;
}

void CPlayer::InitAnimation()
{
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
}

#pragma region CollisionCheck
void CPlayer::OnCollision(CCollider* target)
{
	if (GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup())
	{
		LONG yDiff = 0;
		LONG xDiff = 0;
		if (target->GetBorderPos().left > GetCollider()->GetBorderPos().left)
		{
			xDiff = (GetCollider()->GetBorderPos().right - target->GetBorderPos().left);
		}
		else if (target->GetBorderPos().right < GetCollider()->GetBorderPos().right)
		{
			xDiff = (target->GetBorderPos().right - GetCollider()->GetBorderPos().left);
		}
		else
			xDiff = (GetCollider()->GetBorderPos().right - GetCollider()->GetBorderPos().left);

		// 플레이어 바닥 및 벽 충돌 처리

		// 왼쪽 벽
		if (m_fvCurDir.x < 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 오른쪽에 있을 때
				if (yDiff > xDiff && GetCollider()->GetBorderPos().right > target->GetBorderPos().right)
				{
					fPoint fptPos = GetPos();
					fptPos.x += (float)(target->GetBorderPos().right - GetCollider()->GetBorderPos().left);
					SetPos(fptPos);
				}
			}
		}
		// 오른쪽 벽
		if (m_fvCurDir.x > 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < GetCollider()->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > GetCollider()->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 왼쪽에 있을 때
				if (yDiff > xDiff && GetCollider()->GetBorderPos().left < target->GetBorderPos().left
					&& GetCollider()->GetBorderPos().right > target->GetBorderPos().left)
				{
					fPoint fptPos = GetPos();
					fptPos.x -= (float)(GetCollider()->GetBorderPos().right - target->GetBorderPos().left);
					SetPos(fptPos);
				}
			}
		}

		// 위쪽 / 아래쪽 벽
		if (m_fAccelGravity > 0.f)
		{
			// 위쪽
			if (GetCollider()->GetBorderPos().bottom > target->GetBorderPos().bottom &&
				GetCollider()->GetBorderPos().top <= target->GetBorderPos().bottom)
			{
				yDiff = (target->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					fptPos.y += (float)(target->GetBorderPos().bottom - GetCollider()->GetBorderPos().top);
					SetPos(fptPos);
				}

			}
			// 아래쪽
			if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
				&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
			{
				yDiff = (GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					fPoint fptPos = GetPos();
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					fptPos.y -= (float)(GetCollider()->GetBorderPos().bottom - target->GetBorderPos().top);
					SetPos(fptPos);

					m_bIsGrounded = true;

					m_fAccelGravity = 0.f;
				}
			}
		}
	}
}

void CPlayer::OnCollisionEnter(CCollider* target)
{
	if (GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup())
	{
		if (GetCollider()->GetBorderPos().top < target->GetBorderPos().top
			&& GetCollider()->GetBorderPos().bottom >= target->GetBorderPos().top)
		{
			if (m_eCurState == PLAYER_STATE::JUMP)
			{
				GetAnimator()->FindAnimation(L"Player_Jumpoff_Right")->SetFrame(0);
				GetAnimator()->FindAnimation(L"Player_Jumpoff_Left")->SetFrame(0);

				m_eCurState = PLAYER_STATE::JUMPOFF;
			}
		}
	}
}

void CPlayer::OnCollisionExit(CCollider* target)
{

}
#pragma endregion