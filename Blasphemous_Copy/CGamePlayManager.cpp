#include "framework.h"
#include "CGamePlayManager.h"

CGamePlayManager::CGamePlayManager()
{
	m_pPlayer = nullptr;
}

CGamePlayManager::~CGamePlayManager()
{
}

const vector<CGameObject*>& CGamePlayManager::GetEnemyInScene(GROUP_SCENE eScene)
{
	map<GROUP_SCENE, vector<CGameObject*>>::iterator iter = m_mapEnemy.find(eScene);
	assert(m_mapEnemy.end() != iter);

	return iter->second;
}
