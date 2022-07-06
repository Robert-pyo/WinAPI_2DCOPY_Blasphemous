#include "framework.h"
#include "CScene_Boss.h"
#include "CMap.h"
#include "CWarpPoint.h"
#include "CBackground.h"
#include "CD2DImage.h"
#include "CEnemy.h"

CScene_Boss::CScene_Boss()
{
	m_pBgImg = CResourceManager::GetInst()->LoadD2DImage(L"BossRoom_Background", L"texture\\Map\\BossScene\\BossRoom_Background.png");
}

CScene_Boss::~CScene_Boss()
{
}

void CScene_Boss::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}
}

void CScene_Boss::init()
{
	CSoundManager::GetInst()->AddSound(L"Piedad_BossRoom_Ambient", L"sound\\BGM\\Pietat_Boss_Drone.wav", true);
	CSoundManager::GetInst()->AddSound(L"Piedad_Boss_Fight", L"sound\\BGM\\Pietat_MASTER.wav", true);
}

void CScene_Boss::Enter()
{
	CUIManager::GetInst()->SetKeyControl(false);
	CGameManager::GetInst()->SetGameStart(true);

	CSoundManager::GetInst()->Play(L"Piedad_BossRoom_Ambient");

	// 타일 로딩
	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"texture\\Map\\Tileset\\Tilemaps\\Boss_Groundtiles.tile";
	LoadTile(path);

	CBackground* pBackground = new CBackground;
	pBackground->SetImage(m_pBgImg);
	pBackground->SetTexLeftTop(fPoint(0.f, 0.f));
	pBackground->SetScale(fPoint(m_pBgImg->GetWidth() * 2.f, m_pBgImg->GetHeight() * 2.f));
	AddObject(pBackground, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CMap* pMap = new CMap;
	pMap->Load(L"BossRoom", L"texture\\Map\\BossScene\\Boss.png");
	pMap->SetScale(pMap->GetScale());
	AddObject(pMap, GROUP_GAMEOBJ::FLOOR);

	CWarpPoint* warpToChurch = new CWarpPoint;
	warpToChurch->SetName(L"Church");
	warpToChurch->SetPos(
		fPoint((pMap->GetPos().x + pMap->GetScale().x) - 100.f, pMap->GetPos().y + pMap->GetScale().y - 500.f)
	);
	AddObject(warpToChurch, GROUP_GAMEOBJ::DEFAULT);

	CWarpPoint* warpToCutScene = new CWarpPoint;
	warpToCutScene->SetName(L"BossCutScene");
	warpToCutScene->SetPos(fPoint(1517.f, 932.f));
	AddObject(warpToCutScene, GROUP_GAMEOBJ::DEFAULT);

	CPlayer* pPlayer = (CPlayer*)SpawnObjects(this, "Player");
	CEnemy* pBoss = (CEnemy*)SpawnObjects(this, "Piedad");

	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"BossCutScene")
	{
		CPlayer::GetPlayer()->SetPos(fPoint(warpToCutScene->GetPos().x + 100.f, warpToCutScene->GetPos().y + 50.f));
		pBoss->SetPos(fPoint(pBoss->GetPos().x, pBoss->GetPos().y - 20.f));
		CCameraManager::GetInst()->InitCameraPos(fPoint(warpToCutScene->GetPos().x + 100.f, warpToCutScene->GetPos().y));
		DeleteObj(warpToCutScene);
	}
	else
	{
		CCameraManager::GetInst()->InitCameraPos(
			fPoint(pMap->GetPos().x + pMap->GetScale().x - 600.f, pMap->GetPos().y + pMap->GetScale().y - 600.f));
	}

	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"Church")
	{
		CPlayer::GetPlayer()->SetPos(fPoint(warpToChurch->GetPos().x - 100.f, warpToChurch->GetPos().y));
	}

	CCameraManager::GetInst()->SetBoundary(pMap->GetPos(), pMap->GetPos() + pMap->GetScale());

	CCameraManager::GetInst()->FadeIn(2.0f);
}

void CScene_Boss::Exit()
{
	for (UINT i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; ++i)
	{
		if ((GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::WEAPON) continue;

		ClearGroup((GROUP_GAMEOBJ)i);
	}

	CSoundManager::GetInst()->Stop(L"Piedad_BossRoom_Ambient");
	CSoundManager::GetInst()->Stop(L"Piedad_Boss_Fight");

	// 플레이어가 이 씬을 나가면
	// 이 씬에서는 AddObject되었던 것을 벡터에서만 지워줌
	if (CPlayer::GetPlayer() != nullptr)
	{
		vector<CGameObject*>& vecObj = GetObjGroup(GROUP_GAMEOBJ::PLAYER);
		if (vecObj.size() > 0)
			vecObj.erase(vecObj.begin());
	}
}
