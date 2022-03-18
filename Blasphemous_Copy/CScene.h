#pragma once
#include "CEnemyFactory.h"
#include "CPlayer.h"

// ���� ���� : �ش� Ŭ������ ������ ������ ����� �� �ְ� ����
// 1. ��������� ������ ȣ��Ǿ� #pragma once ����θ� Ȯ�� �Ұ��� ���� �ذ�
// 2. ������ �ð��� �����ų �� ����
class CGameObject;

class CScene
{
private:
	// ���� Scene�� � ������Ʈ���� �����ִ��� vector�� ����
	vector<CGameObject*> m_arrObj[(int)GROUP_GAMEOBJ::SIZE];
	// ���� Scene�� �̸�
	wstring m_sceneName;

	CPlayer* m_pPlayer;

	UINT m_iTileX;
	UINT m_iTileY;

public:
	CScene();
	CScene(const wstring& sceneName);
	virtual ~CScene();

	virtual void update();
	virtual void finalUpdate();
	virtual void render();
	void render_tile();

	virtual void Enter() = 0;	// �� ���� �� �ൿ -> �� ���� �ൿ�� �ٸ� �� �����Ƿ� ���������Լ��� ó��
	virtual void Exit() = 0;	// �� �ƿ� �� �ൿ -> �� ���� �ൿ�� �ٸ� �� �����Ƿ� ���������Լ��� ó��

public:
	void RegisterPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; };
	CPlayer* GetPlayer() { return m_pPlayer; }

	void SetName(const wstring& strName);

	wstring GetName();
	UINT	GetTileX();
	UINT	GetTileY();

	vector<CGameObject*>& GetObjGroup(GROUP_GAMEOBJ group);
	vector<CGameObject*>& GetUIGroup();

	// ���� ���� ���� ������Ʈ �߰�
	void AddObject(CGameObject* pGameObj, GROUP_GAMEOBJ type);

	void CreateTile(UINT xSize, UINT ySize);
	void LoadTile(const wstring& strPath);

	void ClearGroup(GROUP_GAMEOBJ group);
	void ClearAll();
};

