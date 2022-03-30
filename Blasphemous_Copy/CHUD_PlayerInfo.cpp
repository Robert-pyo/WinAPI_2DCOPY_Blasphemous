#include "framework.h"
#include "CHUD_PlayerInfo.h"
#include "CPlayer.h"
#include "CD2DImage.h"

CHUD_PlayerInfo::CHUD_PlayerInfo()
{
	m_pPortraitImg = CResourceManager::GetInst()->LoadD2DImage(L"PlayerPortrait", L"texture\\UI\\HUD\\PlayerInfo\\Health\\PlayerInfo_Portrait.png");
	m_pHealthImg = CResourceManager::GetInst()->LoadD2DImage(L"PlayerHealth", L"texture\\UI\\HUD\\PlayerInfo\\Health\\PlayerInfo_Hp.png");
	m_pMpImg = CResourceManager::GetInst()->LoadD2DImage(L"PlayerMp", L"texture\\UI\\HUD\\PlayerInfo\\Health\\PlayerInfo_Mp.png");

	SetPos(fPoint(20.f, 20.f));
	SetScale(fPoint((float)m_pPortraitImg->GetWidth(), (float)m_pPortraitImg->GetHeight()));

	m_fHpPos = fPoint(100.f, 22.f) + GetPos();
	m_fMpPos = fPoint(155.f, 46.f) + GetPos();
}

CHUD_PlayerInfo::~CHUD_PlayerInfo()
{
}

void CHUD_PlayerInfo::update()
{
	m_pPlayer = CPlayer::GetPlayer();
	if (CPlayer::GetPlayer() != nullptr)
	{
		m_fMaxHP = m_pPlayer->GetPlayerAbility().fMaxHp;
		m_fCurHP = m_pPlayer->GetPlayerAbility().fCurHp;
		m_fMaxMP = m_pPlayer->GetPlayerAbility().fMaxMp;
		m_fCurMP = m_pPlayer->GetPlayerAbility().fCurMp;

		m_sPotionCount = m_pPlayer->GetPlayerAbility().sHpPotionCount;
		m_sMaxPotionCount = m_pPlayer->GetPlayerAbility().sMaxPotionCount;

		m_fCurHP = 270.f * (m_fCurHP / m_fMaxHP);
		m_fCurMP = 180.f * (m_fCurMP / m_fMaxMP);
	}
}

void CHUD_PlayerInfo::render()
{
	CRenderManager::GetInst()->RenderImage(m_pHealthImg,
		m_fHpPos.x, m_fHpPos.y,
		m_fHpPos.x + m_fCurHP,
		m_fHpPos.y + m_pHealthImg->GetHeight() * 2.f
	);

	CRenderManager::GetInst()->RenderImage(m_pMpImg,
		m_fMpPos.x, m_fMpPos.y,
		m_fMpPos.x + m_fCurMP,
		m_fMpPos.y + m_pMpImg->GetHeight() * 2.f
	);

	CRenderManager::GetInst()->RenderImage(m_pPortraitImg,
		GetPos().x, GetPos().y,
		GetPos().x + GetScale().x * 2.f, 
		GetPos().y + GetScale().y * 2.f
	);
}
