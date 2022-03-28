#include "framework.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "CScene_Start.h"
#include "CScene_Stage1.h"
#include "CScene_Tool.h"
#include "CScene_Title.h"
#include "CScene_Tutorial.h"
#include "CScene_Church.h"

CSceneManager::CSceneManager()
{
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; ++i)
	{
		m_arrScene[i] = nullptr;
	}

	m_pCurScene = nullptr;

	m_bDebugMode = false;
}

CSceneManager::~CSceneManager()
{
	// SceneManager가 가지고 있는 모든 씬들을 지워줌 -> 게임이 끝났으므로
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; ++i)
	{
		if (nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(int)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	if (PRESS_KEY_DOWN(VK_F11))
	{
		m_bDebugMode = !m_bDebugMode;
	}

	m_pCurScene->update();
	m_pCurScene->finalUpdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(int)GROUP_SCENE::TITLE] = new CScene_Title();
	m_arrScene[(int)GROUP_SCENE::TITLE]->SetName(L"Title");
	m_arrScene[(int)GROUP_SCENE::TITLE]->init();

	m_arrScene[(int)GROUP_SCENE::TESTSTAGE] = new CScene_Stage1;
	m_arrScene[(int)GROUP_SCENE::TESTSTAGE]->SetName(L"Stage_01");
	m_arrScene[(int)GROUP_SCENE::TESTSTAGE]->init();

	m_arrScene[(int)GROUP_SCENE::TOOL] = new CScene_Tool();
	m_arrScene[(int)GROUP_SCENE::TOOL]->SetName(L"Tool");
	m_arrScene[(int)GROUP_SCENE::TOOL]->init();

	m_arrScene[(int)GROUP_SCENE::TUTORIAL] = new CScene_Tutorial();
	m_arrScene[(int)GROUP_SCENE::TUTORIAL]->SetName(L"Tutorial");
	m_arrScene[(int)GROUP_SCENE::TUTORIAL]->init();

	m_arrScene[(int)GROUP_SCENE::CHURCH] = new CScene_Church();
	m_arrScene[(int)GROUP_SCENE::CHURCH]->SetName(L"Church");
	m_arrScene[(int)GROUP_SCENE::CHURCH]->init();

	m_pCurScene = m_arrScene[(int)GROUP_SCENE::CHURCH];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurrentScene()
{
	return m_pCurScene;
}
