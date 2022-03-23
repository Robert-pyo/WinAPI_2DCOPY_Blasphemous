#include "framework.h"
#include "CPlayerSword.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CEffect_SwordSlash.h"
#include "CAnimation.h"

CPlayerSword::CPlayerSword()
{
	SetName(L"Sword_MeaCulpa");
	SetScale(fPoint(100.f, 50.f));
	SetAtt(20.f);
	SetAttDuration(0.3f);
	fAccTime = 0.f;
	m_pFxSlash = nullptr;

	m_pImg = CResourceManager::GetInst()->LoadD2DImage(L"Sword_Slash", L"texture\\Player\\penitent_anim_merge.png");

	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_01", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_1.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_02", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_2.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_03", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_3.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_Slash_04", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_SLASH_AIR_4.wav", false);
	CSoundManager::GetInst()->AddSound(L"Penitent_HeavySlash", L"sound\\SoundEffects\\Penitent\\Slash\\PENITENT_HEAVY_SLASH.wav", false);

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::WEAPON, GROUP_GAMEOBJ::ENEMY);
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
}

void CPlayerSword::render()
{
	component_render();
}

void CPlayerSword::Attack()
{
	m_pFxSlash = new CEffect_SwordSlash;
	m_pFxSlash->SetOwnerObj(this);
	m_pFxSlash->SetScale(GetScale());
	CreateObj(m_pFxSlash, GROUP_GAMEOBJ::PLAYER_ATT_FX);

	CGameObject* ownerObj = GetOwnerObj();
	if (ownerObj == nullptr) return;

	CPlayer* user = dynamic_cast<CPlayer*>(ownerObj);

	m_pFxSlash->SetAttCount(user->GetAttackCount());
	m_pFxSlash->SetFxDir(user->GetDirVector());

	if (nullptr != user)
	{
		SetPos(user->GetPos());
		m_pFxSlash->SetPos(GetPos());
		m_pFxSlash->SetFxStart(true);
		
		switch (user->GetAttackCount())
		{
		case 0:
		{
			if (user->GetDirVector().x > 0.f)
			{
				m_pFxSlash->GetAnimator()->FindAnimation(L"Sword_Combo_1_R")->SetFrame(0);
				m_pFxSlash->GetAnimator()->Play(L"Sword_Combo_1_R");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_01");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
			else
			{
				m_pFxSlash->GetAnimator()->FindAnimation(L"Sword_Combo_1_L")->SetFrame(0);
				m_pFxSlash->GetAnimator()->Play(L"Sword_Combo_1_L");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_01");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
		}
		break;
		case 1:
		{
			if (user->GetDirVector().x > 0.f)
			{
				m_pFxSlash->GetAnimator()->FindAnimation(L"Sword_Combo_2_R")->SetFrame(0);
				m_pFxSlash->GetAnimator()->Play(L"Sword_Combo_2_R");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
			else
			{
				m_pFxSlash->GetAnimator()->FindAnimation(L"Sword_Combo_2_L")->SetFrame(0);
				m_pFxSlash->GetAnimator()->Play(L"Sword_Combo_2_L");
				CSoundManager::GetInst()->Play(L"Penitent_Slash_02");
			}
		}
		break;
		case 2:
		{
			if (user->GetDirVector().x > 0.f)
			{
				m_pFxSlash->GetAnimator()->FindAnimation(L"Sword_Combo_3_R")->SetFrame(0);
				m_pFxSlash->GetAnimator()->Play(L"Sword_Combo_3_R");
				CSoundManager::GetInst()->Play(L"Penitent_HeavySlash");
			}
			else
			{
				m_pFxSlash->GetAnimator()->FindAnimation(L"Sword_Combo_3_L")->SetFrame(0);
				m_pFxSlash->GetAnimator()->Play(L"Sword_Combo_3_L");
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
}
