#pragma once
#include "CPlayer.h"

class CEnemy;

// ���� �÷��� �� �÷��̾��� ������ �÷��̾�� ��ȣ�ۿ� ������
// ������Ʈ���� ������ �ʿ��� �� ������ �� �ֵ��� �ϱ�����
// ���� �÷��� �Ŵ��� Ŭ����
class CGamePlayManager
{
private:
	SINGLETON(CGamePlayManager);

private:
	CPlayer* m_pPlayer;
	// �� ������ enemy���� �����ϱ� ���� map
	map<GROUP_SCENE, vector<CGameObject*>> m_mapEnemy;

public:
	void RegisterPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	CPlayer* GetPlayer() { return m_pPlayer; }

public:
	void  RegisterEnemyFromScene(GROUP_SCENE eScene, CEnemy* pEnemy);
	const vector<CGameObject*>& GetEnemyInScene(GROUP_SCENE eScene);
};
