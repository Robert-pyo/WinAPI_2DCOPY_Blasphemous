#pragma once
// ���� �÷��� �� �÷��̾��� ������ �÷��̾�� ��ȣ�ۿ� ������
// ������Ʈ���� ������ �ʿ��� �� ������ �� �ֵ��� �ϱ�����
// ���� �÷��� �Ŵ��� Ŭ����
class CGamePlayManager
{
private:
	SINGLETON(CGamePlayManager);

private:
	CGameObject* m_pPlayer;
	// �� ������ enemy���� �����ϱ� ���� map
	map<GROUP_SCENE, vector<CGameObject*>> m_mapEnemy;

public:
	void RegisterPlayer(CGameObject* pPlayer) { m_pPlayer = pPlayer; }
	CGameObject* GetPlayer() { return m_pPlayer; }

public:
	const vector<CGameObject*>& GetEnemyInScene(GROUP_SCENE eScene);
};
