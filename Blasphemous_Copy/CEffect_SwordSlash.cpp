#include "framework.h"
#include "CEffect_SwordSlash.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CPlayerSword.h"
#include <time.h>

CEffect_SwordSlash::CEffect_SwordSlash()
{
	LoadEffectImg(L"FXSwordSlash", L"texture\\Player\\penitent_anim_merge.png");
	SetName(L"FXSwordSlash");

	CreateCollider();
	m_iAttCount = 0;

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Sword_Combo_1_R", GetFxImg(), fPoint(546.f, 576.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, false);
	GetAnimator()->CreateAnimation(L"Sword_Combo_1_L", GetFxImg(), fPoint(546.f, 576.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, true);
	GetAnimator()->CreateAnimation(L"Sword_Combo_2_R", GetFxImg(), fPoint(546.f, 656.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, false);
	GetAnimator()->CreateAnimation(L"Sword_Combo_2_L", GetFxImg(), fPoint(546.f, 656.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, true);
	GetAnimator()->CreateAnimation(L"Sword_Combo_3_R", GetFxImg(), fPoint(546.f, 728.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, false);
	GetAnimator()->CreateAnimation(L"Sword_Combo_3_L", GetFxImg(), fPoint(546.f, 728.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, true);

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER_ATT_FX, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER_ATT_FX, GROUP_GAMEOBJ::ENEMY_ATT_FX);

#pragma region AnimationFrameEdit
	CAnimation* pAnim = GetAnimator()->FindAnimation(L"Sword_Combo_1_R");
	pAnim->GetFrame(0).fptOffset.x += 110.f;
	pAnim->GetFrame(0).fptOffset.y += 50.f;
	pAnim->GetFrame(0).fDuration = 0.15f;
	pAnim->GetFrame(1).fptOffset.x += 95.f;
	pAnim->GetFrame(1).fptOffset.y += 40.f;
	pAnim->GetFrame(2).fptOffset.x += 110.f;
	pAnim->GetFrame(2).fptOffset.y += 40.f;

	pAnim = GetAnimator()->FindAnimation(L"Sword_Combo_1_L");
	pAnim->GetFrame(0).fptOffset.x -= 50.f;
	pAnim->GetFrame(0).fptOffset.y += 50.f;
	pAnim->GetFrame(0).fDuration = 0.15f;
	pAnim->GetFrame(1).fptOffset.x -= 25.f;
	pAnim->GetFrame(1).fptOffset.y += 40.f;
	pAnim->GetFrame(2).fptOffset.x -= 25.f;
	pAnim->GetFrame(2).fptOffset.y += 40.f;

	pAnim = GetAnimator()->FindAnimation(L"Sword_Combo_2_R");
	pAnim->GetFrame(0).fptOffset.x += 150.f;
	pAnim->GetFrame(0).fptOffset.y += 50.f;
	pAnim->GetFrame(0).fDuration = 0.15f;
	pAnim->GetFrame(1).fptOffset.x += 90.f;
	pAnim->GetFrame(1).fptOffset.y += 75.f;
	pAnim->GetFrame(2).fptOffset.x += 110.f;
	pAnim->GetFrame(2).fptOffset.y += 40.f;

	pAnim = GetAnimator()->FindAnimation(L"Sword_Combo_2_L");
	pAnim->GetFrame(0).fptOffset.x -= 70.f;
	pAnim->GetFrame(0).fptOffset.y += 50.f;
	pAnim->GetFrame(0).fDuration = 0.15f;
	pAnim->GetFrame(1).fptOffset.x += 40.f;
	pAnim->GetFrame(1).fptOffset.y += 90.f;
	pAnim->GetFrame(2).fptOffset.x += 5.f;
	pAnim->GetFrame(2).fptOffset.y += 40.f;

	pAnim = GetAnimator()->FindAnimation(L"Sword_Combo_3_R");
	pAnim->GetFrame(0).fptOffset.x += 170.f;
	pAnim->GetFrame(0).fDuration = 0.2f;
	pAnim->GetFrame(1).fptOffset.x += 100.f;
	pAnim->GetFrame(1).fptOffset.y += 120.f;
	pAnim->GetFrame(1).fDuration = 0.2f;
	pAnim->GetFrame(2).fptOffset.x += 70.f;
	pAnim->GetFrame(2).fptOffset.y += 140.f;
	pAnim->GetFrame(2).fDuration = 0.1f;

	pAnim = GetAnimator()->FindAnimation(L"Sword_Combo_3_L");
	pAnim->GetFrame(0).fptOffset.x -= 110.f;
	pAnim->GetFrame(0).fDuration = 0.2f;
	pAnim->GetFrame(1).fptOffset.x -= 20.f;
	pAnim->GetFrame(1).fptOffset.y += 135.f;
	pAnim->GetFrame(1).fDuration = 0.2f;
	pAnim->GetFrame(2).fptOffset.x -= 10.f;
	pAnim->GetFrame(2).fptOffset.y += 160.f;
	pAnim->GetFrame(2).fDuration = 0.1f;
#pragma endregion
}

CEffect_SwordSlash::~CEffect_SwordSlash()
{
}

CEffect_SwordSlash* CEffect_SwordSlash::Clone()
{
	return new CEffect_SwordSlash(*this);
}

void CEffect_SwordSlash::update()
{
	switch (m_iAttCount)
	{
	case 0:
	case 1:
	{
		GetCollider()->SetScale(fPoint(170.f, 70.f));
		SetDuration(GetAnimator()->FindAnimation(L"Sword_Combo_1_R")->GetAnimDuration());

		if (GetFxDir().x > 0.f)
		{
			GetCollider()->SetOffsetPos(fPoint(110.f, 0.f));
		}
		else
		{
			GetCollider()->SetOffsetPos(fPoint(-50.f, 0.f));
		}
	}
		break;
	case 2:
	{
		GetCollider()->SetScale(fPoint(180.f, 100.f));
		SetDuration(GetAnimator()->FindAnimation(L"Sword_Combo_3_R")->GetAnimDuration());

		if (GetFxDir().x > 0.f)
		{
			GetCollider()->SetOffsetPos(fPoint(100.f, 20.f));
		}
		else
		{
			GetCollider()->SetOffsetPos(fPoint(-35.f, 20.f));
		}
	}
		break;
	}

	static float fxAccTime = 0.f;
	if (IsFxStart())
	{
		fxAccTime += fDeltaTime;
	}
	if (GetDuration() <= fxAccTime)
	{
		fxAccTime = 0.f;
		DeleteObj(this);
	}

	GetAnimator()->update();
}

void CEffect_SwordSlash::render()
{
	component_render();
}

void CEffect_SwordSlash::OnCollisionEnter(CCollider* other)
{
	if (GROUP_GAMEOBJ::ENEMY == other->GetOwnerObj()->GetObjGroup())
	{
		CEnemy* enemy = (CEnemy*)other->GetOwnerObj();

		CPlayerSword* ownerObj = (CPlayerSword*)GetOwnerObj();
		if (ownerObj == nullptr) return;

		CPlayer* user = dynamic_cast<CPlayer*>(ownerObj->GetOwnerObj());

		enemy->Hit(user);

		user->SetAttackCount(user->GetAttackCount() + 1);

		srand(time(NULL));

		USHORT randNum = rand() % 4;

		switch (randNum)
		{
		case 0:
			CSoundManager::GetInst()->Play(L"Enemy_Hit1");
			break;
		case 1:
			CSoundManager::GetInst()->Play(L"Enemy_Hit2");
			break;
		case 2:
			CSoundManager::GetInst()->Play(L"Enemy_Hit3");
			break;
		case 3:
			CSoundManager::GetInst()->Play(L"Enemy_Hit4");
			break;
		default:
			assert(nullptr);
			break;
		}
	}
}
