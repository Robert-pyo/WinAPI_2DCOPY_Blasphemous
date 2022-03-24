#include "framework.h"
#include "CHUD_PlayerInfo.h"
#include "CPlayer.h"

CHUD_PlayerInfo::CHUD_PlayerInfo()
{
	SetImage(CResourceManager::GetInst()->LoadD2DImage(L"PlayerInfo", L"texture\\UI\\HUD\\PlayerInfo\\"));

	m_fMaxHP = m_pPlayer->GetPlayerAbility().fMaxHp;
	m_fCurHP = m_pPlayer->GetPlayerAbility().fCurHp;
	m_fMaxMP = m_pPlayer->GetPlayerAbility().fMaxMp;
	m_fCurMP = m_pPlayer->GetPlayerAbility().fCurMp;

	m_sPotionCount = m_pPlayer->GetPlayerAbility().sHpPotionCount;
	m_sMaxPotionCount = m_pPlayer->GetPlayerAbility().sMaxPotionCount;
}

CHUD_PlayerInfo::~CHUD_PlayerInfo()
{
}

CHUD_PlayerInfo* CHUD_PlayerInfo::Clone()
{
	return new CHUD_PlayerInfo(*this);
}

void CHUD_PlayerInfo::update()
{
}

void CHUD_PlayerInfo::render()
{
}
