#include "framework.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Player", L"\\texture\\Player\\penitent_anim_merge.png");
	InitObject(fPoint(700.f, 0.f), fPoint(44.f, 96.f));
	m_strName		= L"Player";
	m_fVelocity		= 0.f;
	m_fMaxVelocity	= 400.f;
	m_fAccelGravity	= 0.f;
	m_fFrictionValue = 1000.f;
	m_fJumpPower	= -550.f;
	m_bIsJumping	= false;
	m_bIsGrounded	= false;
	m_bIsActing		= false;
	m_fvCurDir		= {1.0f, 0.f};
	m_fvPrevDir		= {};

	m_eCurState = PLAYER_STATE::IDLE;

	CreateCollider();
	GetCollider()->SetFinalPos(GetPos());
	GetCollider()->SetOffsetPos(fPoint(33.f, 28.f));
	GetCollider()->SetScale(fPoint(GetScale().x - 10.f, GetScale().y));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle_Right", m_pImg, fPoint(0.f, 0.f), fPoint(71.f, 77.f), fPoint(71.f, 0.f), 0.1f, 13, true);
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pImg, fPoint(29.f, 77.f), fPoint(71.f, 77.f), fPoint(71.f, 0.f), 0.1f, 13, true);
	GetAnimator()->CreateAnimation(L"Player_Running_Right", m_pImg, fPoint(0.f, 155.f), fPoint(77.f, 77.f), fPoint(78.f, 0.f), 0.045f, 14, true);
	GetAnimator()->CreateAnimation(L"Player_Running_Left", m_pImg, fPoint(19.f, 236.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0.045f, 14, true);
	GetAnimator()->CreateAnimation(L"Player_StartRun_Right", m_pImg, fPoint(0.f, 309.f), fPoint(77.f, 77.f), fPoint(78.f, 0.f), 0.045f, 8, false);
	GetAnimator()->CreateAnimation(L"Player_StartRun_Left", m_pImg, fPoint(1.f, 386.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0.045f, 8, false);

	CAnimation* pAnim;
	pAnim = GetAnimator()->FindAnimation(L"Player_Idle_Left");
	for (int i = 0; i < 13; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 60.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Running_Left");
	for (int i = 0; i < 14; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 60.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_StartRun_Left");
	for (int i = 0; i < 8; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 60.f;
	}

	GetAnimator()->Play(L"Player_Idle_Right");
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
	/*if (PRESS_KEY(VK_LBUTTON))
	{
		fPoint mousePos = CCameraManager::getInst()->GetRealPos(MOUSE_POS());
		m_fAccelGravity = 0.f;
		SetPos(mousePos);
	}*/

	update_move();
	update_state();
	update_animation();

	CCameraManager::getInst()->SetLookAt(GetPos());

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_fvPrevDir = m_fvCurDir;
}

void CPlayer::update_state()
{
	if (PRESS_KEY_DOWN('A'))
	{
		m_fvCurDir.x = -1;
		m_bIsActing = true;
		m_eCurState = PLAYER_STATE::RUN;

		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_Running_Left");
		pAnim->SetFrame(0);
	}

	if (PRESS_KEY_DOWN('D'))
	{
		m_fvCurDir.x = 1;
		m_bIsActing = true;
		m_eCurState = PLAYER_STATE::RUN;

		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_Running_Right");
		pAnim->SetFrame(0);
	}

	if (m_fVelocity == 0.f && !m_bIsActing)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
}

void CPlayer::update_move()
{
	if (PRESS_KEY('A'))
	{
		m_fVelocity += 2000.f * fDeltaTime;
	}
	
	if (PRESS_KEY('D'))
	{
		m_fVelocity += 2000.f * fDeltaTime;
	}

	if (PRESS_KEY_DOWN(VK_SPACE) && m_bIsGrounded)
	{
		Jump();
	}

	float fFriction = m_fvCurDir.x * (-1) * m_fFrictionValue * fDeltaTime;

	if (m_fvCurDir.x > 0.f)
	{
		if (m_fVelocity <= abs(fFriction))
		{
			m_fVelocity = 0.f;
			m_bIsActing = false;
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
			m_bIsActing = false;
		}
		else
		{
			m_fVelocity -= fFriction;
		}
	}
	m_fptPos.x += (float)(m_fvCurDir.x * m_fVelocity * fDeltaTime);
	m_fptPos.y += (float)(m_fAccelGravity * fDeltaTime);

	m_fAccelGravity += (float)(GRAVITY * fDeltaTime);
	if (m_fAccelGravity >= 1000.f)
		m_fAccelGravity = 1000.f;
	if (m_fVelocity >= m_fMaxVelocity)
		m_fVelocity = m_fMaxVelocity;

}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_fvPrevDir == m_fvCurDir)
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
	}
		break;
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
	}
		break;
	}
}

void CPlayer::render()
{
	/*fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetCollider()->GetFinalPos());
	Rectangle(hDC,
		(int)(fptRenderPos.x - m_fptScale.x / 2.f),
		(int)(fptRenderPos.y - m_fptScale.y / 2.f),
		(int)(fptRenderPos.x + m_fptScale.x / 2.f),
		(int)(fptRenderPos.y + m_fptScale.y / 2.f));*/

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

void CPlayer::OnCollision(CCollider* target)
{
	if (GROUP_GAMEOBJ::FLOOR == target->GetOwnerObj()->GetObjGroup())
	{
		LONG yDiff = 0;
		LONG xDiff = 0;
		if (target->GetBorderPos().left > m_pCollider->GetBorderPos().left)
		{
			xDiff = (m_pCollider->GetBorderPos().right - target->GetBorderPos().left);
		}
		else if (target->GetBorderPos().right < m_pCollider->GetBorderPos().right)
		{
			xDiff = (target->GetBorderPos().right - m_pCollider->GetBorderPos().left);
		}
		else
			xDiff = (m_pCollider->GetBorderPos().right - m_pCollider->GetBorderPos().left);

		// 플레이어 바닥 및 벽 충돌 처리

		// 왼쪽 벽
		if (m_fvCurDir.x < 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < m_pCollider->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > m_pCollider->GetBorderPos().top)
			{
				yDiff = (m_pCollider->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 오른쪽에 있을 때
				if (yDiff > xDiff && m_pCollider->GetBorderPos().right > target->GetBorderPos().right)
				{
					m_fptPos.x += (float)(target->GetBorderPos().right - m_pCollider->GetBorderPos().left) * 10.f * fDeltaTime;
				}
			}
		}
		// 오른쪽 벽
		if (m_fvCurDir.x > 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < m_pCollider->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > m_pCollider->GetBorderPos().top)
			{
				yDiff = (m_pCollider->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 왼쪽에 있을 때
				if (yDiff > xDiff && m_pCollider->GetBorderPos().left < target->GetBorderPos().left
					&& m_pCollider->GetBorderPos().right > target->GetBorderPos().left)
				{
					m_fptPos.x -= (float)(m_pCollider->GetBorderPos().right - target->GetBorderPos().left) * 10.f * fDeltaTime;
				}
			}
		}

		// 위쪽 / 아래쪽 벽
		if (m_fAccelGravity > 0.f)
		{
			// 위쪽
			if (m_pCollider->GetBorderPos().bottom > target->GetBorderPos().bottom &&
				m_pCollider->GetBorderPos().top <= target->GetBorderPos().bottom)
			{
				yDiff = (target->GetBorderPos().bottom - m_pCollider->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					m_fptPos.y += (float)(target->GetBorderPos().bottom - m_pCollider->GetBorderPos().top) * 10.f * fDeltaTime;
				}

			}
			// 아래쪽
			if (m_pCollider->GetBorderPos().top < target->GetBorderPos().top
				&& m_pCollider->GetBorderPos().bottom >= target->GetBorderPos().top)
			{
				yDiff = (m_pCollider->GetBorderPos().bottom - target->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					m_fptPos.y -= (float)(m_pCollider->GetBorderPos().bottom - target->GetBorderPos().top) * 10.f * fDeltaTime;

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

	}
}

void CPlayer::OnCollisionExit(CCollider* target)
{

}