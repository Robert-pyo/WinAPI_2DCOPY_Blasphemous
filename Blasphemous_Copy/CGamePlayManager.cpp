#include "framework.h"
#include "CGamePlayManager.h"
#include "CEnemy.h"

CGamePlayManager::CGamePlayManager()
{
	m_pPlayer = nullptr;
}

CGamePlayManager::~CGamePlayManager()
{
}

void CGamePlayManager::RegisterEnemyToScene(GROUP_SCENE eScene, CEnemy* pEnemy)
{
	map<GROUP_SCENE, vector<CGameObject*>>::iterator iter = m_mapEnemy.find(eScene);
	assert(m_mapEnemy.end() != iter);

	for (UINT i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == pEnemy->GetName())
		{
			return;
		}
		else
		{
			iter->second.push_back(pEnemy);
		}
	}
}

const vector<CGameObject*>& CGamePlayManager::GetEnemyInScene(GROUP_SCENE eScene)
{
	map<GROUP_SCENE, vector<CGameObject*>>::iterator iter = m_mapEnemy.find(eScene);
	assert(m_mapEnemy.end() != iter);

	return iter->second;
}
