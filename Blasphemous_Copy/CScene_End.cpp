#include "framework.h"
#include "CScene_End.h"
#include "CBackground.h"
#include "CD2DImage.h"

CScene_End::CScene_End()
{
	m_pBGImg = CResourceManager::GetInst()->LoadD2DImage(L"EndingBackground", L"texture\\UI\\Background\\Ending\\death-sreen-title.png");
	m_fInputDelay = 0.f;
}

CScene_End::~CScene_End()
{
}

void CScene_End::update()
{
	m_fInputDelay += fDeltaTime;

	if (m_fInputDelay > 3)
	{
		if (PRESS_ANY_KEY())
		{
			CCameraManager::GetInst()->FadeOut(2.f);
			ChangeToNextScene(GROUP_SCENE::TITLE);
			CSceneManager::GetInst()->RestartScenes();
		}
	}
}

void CScene_End::init()
{
}

void CScene_End::Enter()
{
	vector<CGameObject*> vecObj = GetObjGroup(GROUP_GAMEOBJ::PLAYER);

	CCameraManager::GetInst()->FadeIn(2.0f);

	CBackground* pBackground = new CBackground;
	pBackground->SetImage(m_pBGImg);
	pBackground->SetScale(fPoint(m_pBGImg->GetWidth(), m_pBGImg->GetHeight()));
	AddObject(pBackground, GROUP_GAMEOBJ::BACKGROUND_FIXED);
}

void CScene_End::Exit()
{
}
