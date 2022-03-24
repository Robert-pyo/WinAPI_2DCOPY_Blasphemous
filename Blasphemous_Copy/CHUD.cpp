#include "framework.h"
#include "CHUD.h"
#include "CPlayer.h"

CHUD::CHUD()
{
	m_pPlayer = CPlayer::GetPlayer();
	m_pImg = nullptr;
}

CHUD::~CHUD()
{
}
