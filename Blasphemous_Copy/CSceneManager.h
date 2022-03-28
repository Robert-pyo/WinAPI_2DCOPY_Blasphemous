#pragma once
class CScene;

class CSceneManager
{
	friend class CEventManager;

	SINGLETON(CSceneManager);

private:
	// SceneManager
	// Scene���� ������ �־�� ���� ����
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];

	// ���� Scene�� �������� ����
	CScene* m_pCurScene;
	CScene* m_pPrevScene;

	bool m_bDebugMode;

	void ChangeScene(GROUP_SCENE scene);

public:
	void update();
	void render();
	void init();

	CScene* GetCurrentScene();
	CScene* GetPrevScene();
	void RestartScenes();

public:
	bool GetIsDebugging() { return m_bDebugMode; }
};

