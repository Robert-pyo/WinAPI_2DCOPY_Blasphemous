#include "framework.h"
#include "CGameManager.h"
#include "CPlayer.h"
#include "CScene.h"

CGameManager::CGameManager()
{
	m_bDisableControl = false;
}

CGameManager::~CGameManager()
{
}

void CGameManager::update()
{
	if (m_bDisableControl)
	{
		if (CPlayer::GetPlayer() != nullptr)
			CPlayer::GetPlayer()->SetControllable(false);
	}
}

void CGameManager::init()
{
	
}
