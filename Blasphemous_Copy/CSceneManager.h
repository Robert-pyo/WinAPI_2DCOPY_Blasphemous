#pragma once
class CScene;

class CSceneManager
{
	friend class CEventManager;

	SINGLETON(CSceneManager);

private:
	// SceneManager
	// Scene들을 가지고 있어야 관리 가능
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];

	// 현재 Scene이 무엇인지 저장
	CScene* m_pCurScene;

	void ChangeScene(GROUP_SCENE scene);

public:
	void update();
	void render(HDC hDC);
	void init();

	CScene* GetCurrentScene();
};

