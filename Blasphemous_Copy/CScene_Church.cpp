#include "framework.h"
#include "CScene_Church.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CEnemy.h"
#include "CEnemyFactory.h"
#include "CSpawnPoint.h"
#include "CJsonLoader.h"

CScene_Church::CScene_Church()
{
}

CScene_Church::~CScene_Church()
{
	vector<CGameObject*>& vecObj = GetObjGroup(GROUP_GAMEOBJ::PLAYER);
	if (vecObj.size() > 0)
		vecObj.erase(vecObj.begin());
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

	CCameraManager::GetInst()->InitCameraPos(CPlayer::GetPlayer()->GetPos());
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

	CCameraManager::GetInst()->SetBoundary(fPoint(pMap->GetPos().x + 350.f, pMap->GetPos().y), pMap->GetPos() + pMap->GetScale());

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
