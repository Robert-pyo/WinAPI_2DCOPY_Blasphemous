#include "framework.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_pTex = CResourceManager::getInst()->LoadTexture(L"Player", L"\\texture\\Player\\penitent_anim_merge.bmp");
	m_strName = L"Player";
	initObject(fPoint(32.f, 0.f), fPoint(44.f, 96.f));
	m_fVelocity = 300.f;
	m_fAccel = 50.f;
	m_fJumpPower = -550.f;
	m_bIsJumping = false;
	m_bIsGrounded = false;
	m_fvDir = {};
	m_fvChangeXY = {};

	CreateCollider();
	GetCollider()->SetFinalPos(GetPos());
	GetCollider()->SetOffsetPos(fPoint(32.f, 28.f));
	GetCollider()->SetScale(GetScale());

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle_Right", m_pTex, fPoint(0.f, 0.f), fPoint(71.f, 77.f), fPoint(71.f, 0.f), 0.1f, 13, true);
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pTex, fPoint(29.f, 77.f), fPoint(71.f, 77.f), fPoint(71.f, 0.f), 0.1f, 13, true);
	GetAnimator()->CreateAnimation(L"Player_Running_Right", m_pTex, fPoint(0.f, 154.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0.045f, 14, true);
	GetAnimator()->CreateAnimation(L"Player_Running_Left", m_pTex, fPoint(18.f, 231.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0.045f, 14, true);
	GetAnimator()->CreateAnimation(L"Player_StartRun_Right", m_pTex, fPoint(0.f, 308.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0.045f, 8, false);
	GetAnimator()->CreateAnimation(L"Player_StartRun_Left", m_pTex, fPoint(0.f, 385.f), fPoint(78.f, 77.f), fPoint(78.f, 0.f), 0.045f, 8, false);

	CAnimation* pAnim;
	pAnim = GetAnimator()->FindAnimation(L"Player_Idle_Left");
	for (int i = 0; i < 13; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 55.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_Running_Left");
	for (int i = 0; i < 14; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 62.f;
	}

	pAnim = GetAnimator()->FindAnimation(L"Player_StartRun_Left");
	for (int i = 0; i < 8; ++i)
	{
		pAnim->GetFrame(i).fptOffset.x += 62.f;
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
	if (PRESS_KEY(VK_LBUTTON))
	{
		fPoint mousePos = CCameraManager::getInst()->GetRealPos(MOUSE_POS());
		m_fAccel = 0.f;
		SetPos(mousePos);
	}

	if (PRESS_KEY_DOWN(VK_LEFT))
	{
		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_StartRun_Left");
		pAnim->SetFrame(0);

		pAnim = GetAnimator()->FindAnimation(L"Player_Running_Left");
		pAnim->SetFrame(0);
	}
	if (PRESS_KEY(VK_LEFT))
	{
		GetAnimator()->Play(L"Player_StartRun_Left");
		if (GetAnimator()->FindAnimation(L"Player_StartRun_Left")->GetAnimDone())
			GetAnimator()->Play(L"Player_Running_Left");
		m_fvDir.x = -1;
	}
	if (PRESS_KEY_UP(VK_LEFT))
	{
		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_StartRun_Left");
		pAnim->SetAnimDone(false);
		GetAnimator()->Play(L"Player_Idle_Left");
		m_fvDir.x = 0;
	}

	if (PRESS_KEY_DOWN(VK_RIGHT))
	{
		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_StartRun_Right");
		pAnim->SetFrame(0);

		pAnim = GetAnimator()->FindAnimation(L"Player_Running_Right");
		pAnim->SetFrame(0);
	}
	if (PRESS_KEY(VK_RIGHT))
	{
		GetAnimator()->Play(L"Player_StartRun_Right");
		if (GetAnimator()->FindAnimation(L"Player_StartRun_Right")->GetAnimDone())
			GetAnimator()->Play(L"Player_Running_Right");
		m_fvDir.x = 1;
	}
	if (PRESS_KEY_UP(VK_RIGHT))
	{
		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_StartRun_Right");
		pAnim->SetAnimDone(false);
		GetAnimator()->Play(L"Player_Idle_Right");
		m_fvDir.x = 0;
	}

	static fPoint fptCur = {};
	static fPoint fptPrev = {};

	fptPrev = fptCur;

	m_fptPos.x += (float)(m_fvDir.x * m_fVelocity * fDeltaTime);
	m_fptPos.y += (float)(m_fAccel * fDeltaTime);

	fptCur = GetPos();

	m_fvChangeXY = fVector2D(fptCur.x - fptPrev.x, fptPrev.y - fptCur.y);

	// TODO : 점프를 하지 않고 바닥을 벗어났을 경우 IsGrounded가 아니므로 점프 못하게 해야하는데..
	// 플레이어가 향하는 방향을 알면 떨어지고있을 때를 감지할 수 있지 않을까 -> x 변화량 / y 변화량 -> 기울기 -> 방향?
	// -> 성공!
	if (PRESS_KEY_DOWN(VK_SPACE) && !m_bIsJumping && m_bIsGrounded && m_fvChangeXY.y >= 0.f)
	{
		m_bIsJumping = true;
		m_bIsGrounded = false;
	}
	if (m_bIsJumping)
	{
		Jump();
	}

	m_fAccel += (float)(GRAVITY * fDeltaTime);
	if (m_fAccel >= 1000.f)
		m_fAccel = 1000.f;

	GetAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	/*fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetCollider()->GetFinalPos());
	Rectangle(hDC,
		(int)(fptRenderPos.x - m_fptScale.x / 2.f),
		(int)(fptRenderPos.y - m_fptScale.y / 2.f),
		(int)(fptRenderPos.x + m_fptScale.x / 2.f),
		(int)(fptRenderPos.y + m_fptScale.y / 2.f));*/

	component_render(hDC);
}

void CPlayer::init()
{

}

void CPlayer::Jump()
{
	m_fptPos.y += (float)(m_fJumpPower * fDeltaTime);
}

const float CPlayer::GetVelocity()
{
	return m_fVelocity;
}

const fVector2D& CPlayer::GetDirVector()
{
	return m_fvDir;
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
		if (m_fvDir.x < 0.f)
		{
			// y축 위치가 맞지 않는 경우 무시
			if (target->GetBorderPos().top < m_pCollider->GetBorderPos().bottom
				&& target->GetBorderPos().bottom > m_pCollider->GetBorderPos().top)
			{
				yDiff = (m_pCollider->GetBorderPos().bottom - target->GetBorderPos().top);

				// 플레이어가 벽보다 오른쪽에 있을 때
				if (yDiff > xDiff && m_pCollider->GetBorderPos().right > target->GetBorderPos().right)
				{
					m_fptPos.x += (float)(target->GetBorderPos().right - m_pCollider->GetBorderPos().left);
				}
			}
		}
		// 오른쪽 벽
		if (m_fvDir.x > 0.f)
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
					m_fptPos.x -= (float)(m_pCollider->GetBorderPos().right - target->GetBorderPos().left);
				}
			}
		}

		// 위쪽 / 아래쪽 벽
		if (m_fAccel > 0.f)
		{
			// 위쪽
			if (m_pCollider->GetBorderPos().bottom > target->GetBorderPos().bottom &&
				m_pCollider->GetBorderPos().top <= target->GetBorderPos().bottom)
			{
				yDiff = (target->GetBorderPos().bottom - m_pCollider->GetBorderPos().top);

				if (yDiff < xDiff)
				{
					// 충돌시 착지한 경계면에서 뚫고 들어간 정도를 계산하여 현재 위치에 더해줌
					m_fptPos.y += (float)(target->GetBorderPos().bottom - m_pCollider->GetBorderPos().top);
					m_fJumpPower = 0.f;
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
					m_fptPos.y -= (float)(m_pCollider->GetBorderPos().bottom - target->GetBorderPos().top);

					m_bIsGrounded = true;
					m_bIsJumping = false;

					m_fJumpPower = -550.f;
					m_fAccel = 0.f;
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