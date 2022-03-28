#include "framework.h"
#include "CScene_Church.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CEnemy.h"
#include "CEnemyFactory.h"
#include "CSpawnPoint.h"
#include "CJsonLoader.h"
#include "CWarpPoint.h"

CScene_Church::CScene_Church()
{
}

CScene_Church::~CScene_Church()
{
}

void CScene_Church::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}
}

void CScene_Church::init()
{
	SpawnObjects(this, "Stoner");
	SpawnObjects(this, "Player");

	CCameraManager::GetInst()->FollowTargetObj(CPlayer::GetPlayer(), true, true);
}

void CScene_Church::Enter()
{
	CUIManager::GetInst()->SetKeyControl(false);

	// 타일 로딩
	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"texture\\Map\\Tileset\\Tilemaps\\Church_Groundtiles.tile";
	LoadTile(path);

	CMap* pMap = new CMap;
	pMap->Load(L"Church", L"texture\\Map\\BossEntrance\\Church.png");
	pMap->SetScale(pMap->GetScale() / 2.f);
	AddObject(pMap, GROUP_GAMEOBJ::FLOOR);

	CWarpPoint* warpToTutorial = new CWarpPoint;
	warpToTutorial->SetName(L"Tutorial");
	warpToTutorial->SetPos(fPoint(pMap->GetPos().x + 100.f, pMap->GetPos().y + pMap->GetScale().y - 100.f));
	AddObject(warpToTutorial, GROUP_GAMEOBJ::DEFAULT);

	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"Tutorial")
	{
		CPlayer::GetPlayer()->SetPos(fPoint(warpToTutorial->GetPos().x + 80.f, warpToTutorial->GetPos().y));
	}

	CCameraManager::GetInst()->SetBoundary(fPoint(pMap->GetPos().x + 350.f, pMap->GetPos().y), pMap->GetPos() + pMap->GetScale());
	CCameraManager::GetInst()->InitCameraPos((pMap->GetPos() + pMap->GetScale()) / 2.f);

	CCameraManager::GetInst()->FadeIn(2.0f);
}

void CScene_Church::Exit()
{
	for (UINT i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; ++i)
	{
		if ((GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::ENEMY
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER_ATT_FX || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::ENEMY_ATT_FX
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::WEAPON) continue;

		ClearGroup((GROUP_GAMEOBJ)i);
	}
}
