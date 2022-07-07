#include "framework.h"
#include "CScene_Church.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CEnemy.h"
#include "CEnemyFactory.h"
#include "CSpawnPoint.h"
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

#ifdef _DEBUG
	if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}
#endif
}

void CScene_Church::init()
{
	SpawnObjects(this, "Stoner");

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
	warpToTutorial->SetPos(fPoint(pMap->GetPos().x + pMap->GetScale().x - 100.f, pMap->GetPos().y + pMap->GetScale().y - 100.f));
	AddObject(warpToTutorial, GROUP_GAMEOBJ::DEFAULT);

	CWarpPoint* warpToBossRoom = new CWarpPoint;
	warpToBossRoom->SetName(L"Boss");
	warpToBossRoom->SetPos(fPoint(pMap->GetPos().x + 100.f, pMap->GetPos().y + pMap->GetScale().y - 100.f));
	AddObject(warpToBossRoom, GROUP_GAMEOBJ::DEFAULT);

	SpawnObjects(this, "Player");

	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"Tutorial")
	{
		CPlayer::GetPlayer()->SetPos(fPoint(warpToTutorial->GetPos().x - 100.f, warpToTutorial->GetPos().y));
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
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::WEAPON) continue;

		ClearGroup((GROUP_GAMEOBJ)i);
	}

	// 플레이어가 이 씬을 나가면
	// 이 씬에서는 AddObject되었던 것을 벡터에서만 지워줌
	if (CPlayer::GetPlayer() != nullptr)
	{
		vector<CGameObject*>& vecObj = GetObjGroup(GROUP_GAMEOBJ::PLAYER);
		if (vecObj.size() > 0)
			vecObj.erase(vecObj.begin());
	}
}
