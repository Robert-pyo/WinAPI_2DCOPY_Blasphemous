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

	void ChangeScene(GROUP_SCENE scene);

public:
	void update();
	void render(HDC hDC);
	void init();

	CScene* GetCurrentScene();
};

