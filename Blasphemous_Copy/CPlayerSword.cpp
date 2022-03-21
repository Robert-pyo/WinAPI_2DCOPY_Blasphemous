#include "framework.h"
#include "CPlayerSword.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayerSword::CPlayerSword()
{
	SetName(L"Sword_MeaCulpa");
	SetScale(fPoint(100.f, 50.f));
	SetAtt(20.f);
	SetAttDuration(0.3f);
	fAccTime = 0.f;

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON, GROUP_GAMEOBJ::ENEMY);

	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Sword_Slash", L"texture\\Player\\penitent_anim_merge.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Sword_Combo_1_R", m_pImg, fPoint(546.f, 576.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.1f, 4, false, false);
	GetAnimator()->CreateAnimation(L"Sword_Combo_1_L", m_pImg, fPoint(546.f, 576.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.1f, 4, false, true);
	GetAnimator()->CreateAnimation(L"Sword_Combo_2_R", m_pImg, fPoint(546.f, 656.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, false);
	GetAnimator()->CreateAnimation(L"Sword_Combo_2_L", m_pImg, fPoint(546.f, 656.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, true);
	GetAnimator()->CreateAnimation(L"Sword_Combo_3_R", m_pImg, fPoint(546.f, 728.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, false);
	GetAnimator()->CreateAnimation(L"Sword_Combo_3_L", m_pImg, fPoint(546.f, 728.f), fPoint(110.f, 72.f), fPoint(110.f, 0.f), 0, 0.05f, 4, false, true);

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

	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_01", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_1.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_02", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_2.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_03", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_3.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_04", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_4.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_HeavySlash", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_HEAVY_SLASH.wav", false);
}

CPlayerSword::~CPlayerSword()
{
}

CPlayerSword* CPlayerSword::Clone()
{
	return new CPlayerSword(*this);
}

void CPlayerSword::update()
{
	fAccTime += fDeltaTime;

	CGameObject* ownerObj = GetOwnerObj();
	if (ownerObj == nullptr) return;

	CPlayer* user = dynamic_cast<CPlayer*>(ownerObj);

	if (user->GetAttackCount() < 2)
	{
		if (fAccTime > 0.5f)
		{
			GetCollider()->SetOffsetPos(fPoint(0.f, -10000.f));
			fAccTime = 0.f;
		}
	}
	else if (user->GetAttackCount() == 2)
	{
		if (fAccTime > GetAnimator()->FindAnimation(L"Sword_Combo_3_R")->GetAnimDuration())
		{
			GetCollider()->SetOffsetPos(fPoint(0.f, -10000.f));
			fAccTime = 0.f;
		}
	}

	GetAnimator()->update();
}

void CPlayerSword::render()
{
	component_render();
}

void CPlayerSword::Attack()
{
	CGameObject* ownerObj = GetOwnerObj();
	if (ownerObj == nullptr) return;

	CPlayer* user = dynamic_cast<CPlayer*>(ownerObj);

	if (nullptr != user)
	{
		SetPos(user->GetPos());
		
		switch (user->GetAttackCount())
		{
		case 0:
		{
			GetCollider()->SetScale(fPoint(170.f, 70.f));
			if (user->GetDirVector().x > 0.f)
			{
				GetCollider()->SetOffsetPos(fPoint(110.f, 0.f));
				GetAnimator()->FindAnimation(L"Sword_Combo_1_R")->SetFrame(0);
				GetAnimator()->Play(L"Sword_Combo_1_R");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_01");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
			else
			{
				GetCollider()->SetOffsetPos(fPoint(-50.f, 0.f));
				GetAnimator()->FindAnimation(L"Sword_Combo_1_L")->SetFrame(0);
				GetAnimator()->Play(L"Sword_Combo_1_L");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_01");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
		}
		break;
		case 1:
		{
			GetCollider()->SetScale(fPoint(170.f, 70.f));
			if (user->GetDirVector().x > 0.f)
			{
				GetCollider()->SetOffsetPos(fPoint(110.f, 0.f));
				GetAnimator()->FindAnimation(L"Sword_Combo_2_R")->SetFrame(0);
				GetAnimator()->Play(L"Sword_Combo_2_R");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
			else
			{
				GetCollider()->SetOffsetPos(fPoint(-60.f, 20.f));
				GetAnimator()->FindAnimation(L"Sword_Combo_2_L")->SetFrame(0);
				GetAnimator()->Play(L"Sword_Combo_2_L");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
		}
		break;
		case 2:
		{
			GetCollider()->SetScale(fPoint(180.f, 100.f));
			if (user->GetDirVector().x > 0.f)
			{
				GetCollider()->SetOffsetPos(fPoint(100.f, 20.f));
				GetAnimator()->FindAnimation(L"Sword_Combo_3_R")->SetFrame(0);
				GetAnimator()->Play(L"Sword_Combo_3_R");
				CSoundManager::GetInst()->Play(L"Penitent_HeavySlash");
			}
			else
			{
				GetCollider()->SetOffsetPos(fPoint(-35.f, 20.f));
				GetAnimator()->FindAnimation(L"Sword_Combo_3_L")->SetFrame(0);
				GetAnimator()->Play(L"Sword_Combo_3_L");
				CSoundManager::GetInst()->Play(L"Penitent_HeavySlash");
			}
		}
		break;

		default:
			break;
		}
	}
}

void CPlayerSword::OnCollision(CCollider* other)
{
}

void CPlayerSword::OnCollisionEnter(CCollider* other)
{
	if (GROUP_GAMEOBJ::ENEMY == other->GetOwnerObj()->GetObjGroup())
	{
		CEnemy* enemy = (CEnemy*)other->GetOwnerObj();

		CGameObject* ownerObj = GetOwnerObj();
		if (ownerObj == nullptr) return;

		CPlayer* user = dynamic_cast<CPlayer*>(ownerObj);

		enemy->Hit(user);

		user->SetAttackCount(user->GetAttackCount() + 1);
		GetCollider()->SetOffsetPos(fPoint(0.f, -10000.f));
	}
}
