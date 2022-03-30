#include "framework.h"
#include "CBossPatern_GroundSmash.h"
#include "CEnemy.h"
#include "CAnimator.h"
#include "CAnimation.h"

CBossPatern_GroundSmash::CBossPatern_GroundSmash(ENEMY_STATE eEnmState)
	: CState(eEnmState)
{
	m_fAttAccTime = 0.f;

	CSoundManager::GetInst()->AddSound(L"Piedad_SmashScreamVoice", L"sound\\SoundEffects\\Piedad\\PIETAT_SMASH_SCREAM_VOICE.wav", false);
	CSoundManager::GetInst()->AddSound(L"Piedad_SmashVoice", L"sound\\SoundEffects\\Piedad\\PIETAT_SMASH_VOICE.wav", false);
	CSoundManager::GetInst()->AddSound(L"Piedad_Smash", L"sound\\SoundEffects\\Piedad\\PietatSmash.wav", false);
}

CBossPatern_GroundSmash::~CBossPatern_GroundSmash()
{
}

void CBossPatern_GroundSmash::update()
{
	m_fAttAccTime += fDeltaTime;

	GetEnemy()->Attack();

	if (GetEnemy()->GetAnimator()->GetCurAnim()->GetAnimDuration() < m_fAttAccTime)
	{
		ChangeAIState(GetAI(), ENEMY_STATE::TRACE);
		GetEnemy()->SetAttCount(0);
		m_fAttAccTime = 0.f;
	}
}

void CBossPatern_GroundSmash::Enter()
{
	CSoundManager::GetInst()->Play(L"Piedad_SmashScreamVoice");
}

void CBossPatern_GroundSmash::Exit()
{
}
