#pragma once
#include "CEnemyFactory.h"
#include "CPlayer.h"

// ���� ���� : �ش� Ŭ������ ������ ������ ����� �� �ְ� ����
// 1. ��������� ������ ȣ��Ǿ� #pragma once ����θ� Ȯ�� �Ұ��� ���� �ذ�
// 2. ������ �ð��� �����ų �� ����
class CGameObject;
class CUI;

class CScene
{
private:
	// ���� Scene�� � ������Ʈ���� �����ִ��� vector�� ����
	vector<CGameObject*> m_arrObj[(int)GROUP_GAMEOBJ::SIZE];
	// ���� Scene�� �̸�
	wstring m_sceneName;

	UINT m_iTileX;
	UINT m_iTileY;

	vector<CUI*> m_vecUI;

	bool m_IsPaused;

private:
	multimap<string, fPoint> m_mapSpawnPoint;

public:
	CScene();
	CScene(const wstring& sceneName);
	virtual ~CScene();

	virtual void update();
	virtual void finalUpdate();
	virtual void render();
	void render_tile();

	virtual void init();

	virtual void Enter() = 0;	// �� ���� �� �ൿ -> �� ���� �ൿ�� �ٸ� �� �����Ƿ� ���������Լ��� ó��
	virtual void Exit() = 0;	// �� �ƿ� �� �ൿ -> �� ���� �ൿ�� �ٸ� �� �����Ƿ� ���������Լ��� ó��

public:
	void SetName(const wstring& strName);
	wstring GetName();

	UINT	GetTileX();
	UINT	GetTileY();

public:
	void RegisterUI(CUI* pUI);
	CUI* GetUI(const CUI* pUI);

	void UIOptionSelector();

public:
	vector<CGameObject*>& GetObjGroup(GROUP_GAMEOBJ group);
	vector<CGameObject*>& GetUIGroup();

public:
	// ���� ���� ���� ������Ʈ �߰�
	void AddObject(CGameObject* pGameObj, GROUP_GAMEOBJ type);

	void LoadTile(const wstring& strPath);

	void SpawnObjects(CScene* targetScene, const string objName);

	void ClearGroup(GROUP_GAMEOBJ group);
	void ClearAll();
};

