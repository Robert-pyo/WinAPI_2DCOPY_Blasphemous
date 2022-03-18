#pragma once
// 게임 플레이 중 플레이어의 정보나 플레이어와 상호작용 가능한
// 오브젝트들을 씬에서 필요할 때 전달할 수 있도록 하기위한
// 게임 플레이 매니저 클래스
class CGamePlayManager
{
private:
	SINGLETON(CGamePlayManager);

private:
	CGameObject* m_pPlayer;
	// 씬 마다의 enemy들을 관리하기 위한 map
	map<GROUP_SCENE, vector<CGameObject*>> m_mapEnemy;

public:
	void RegisterPlayer(CGameObject* pPlayer) { m_pPlayer = pPlayer; }
	CGameObject* GetPlayer() { return m_pPlayer; }

public:
	const vector<CGameObject*>& GetEnemyInScene(GROUP_SCENE eScene);
};
