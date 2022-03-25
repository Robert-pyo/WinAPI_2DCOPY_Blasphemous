#include "framework.h"
#include "CScene_Tutorial.h"
#include "CD2DImage.h"
#include "CBackground.h"
#include "CMap.h"
#include "CJsonLoader.h"
#include "CSpawnPoint.h"
#include "CPlayer.h"

CScene_Tutorial::CScene_Tutorial()
{
	m_pBgImage = CResourceManager::GetInst()->LoadD2DImage(L"TutorialMapBg", L"texture\\Map\\TutorialScene\\Forest_Background.png");
}

CScene_Tutorial::~CScene_Tutorial()
{
	// 플레이어가 생성된 곳에서 delete 될 수 있도록
	// 이 씬에서는 AddObject되었던 것을 벡터에서만 지워줌
	vector<CGameObject*>& vecObj = GetObjGroup(GROUP_GAMEOBJ::PLAYER);
	if (vecObj.size() > 0)
		vecObj.erase(vecObj.begin());
}

void CScene_Tutorial::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}

	/*if (PRESS_KEY('A'))
	{
		CCameraManager::GetInst()->Scroll(fVector2D(-1, 0), 500.f);
	}
	if (PRESS_KEY('D'))
	{
		CCameraManager::GetInst()->Scroll(fVector2D(1, 0), 500.f);
	}
	if (PRESS_KEY('W'))
	{
		CCameraManager::GetInst()->Scroll(fVector2D(0, -1), 500.f);
	}
	if (PRESS_KEY('S'))
	{
		CCameraManager::GetInst()->Scroll(fVector2D(0, 1), 500.f);
	}*/
}

void CScene_Tutorial::Enter()
{
	// 타일 로딩
	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"texture\\Map\\Tileset\\Tilemaps\\GroundTiles.tile";
	LoadTile(path);

	CSpawnPoint* playerSpawnPoint = new CSpawnPoint;
	m_mapSpawnPoint = CJsonLoader::LoadSpawnPoint();
	map<string, fPoint>::iterator iter = m_mapSpawnPoint.find("Player");
	if (m_mapSpawnPoint.end() != iter)
	{
		playerSpawnPoint->SetName(L"playerSpawnPoint");
		playerSpawnPoint->SetPos(iter->second);
	}
	AddObject(playerSpawnPoint, GROUP_GAMEOBJ::DEFAULT);

	// 플레이어 생성
	CPlayer* pPlayer = CPlayer::GetPlayer();
	pPlayer->SetPos(playerSpawnPoint->GetPos());
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	CBackground* pBackground = new CBackground;
	pBackground->SetImage(m_pBgImage);
	pBackground->SetTexLeftTop(fPoint(0.f, 0.f));
	pBackground->SetScale(fPoint(m_pBgImage->GetWidth() * 2.f, m_pBgImage->GetHeight() * 2.f));
	AddObject(pBackground, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CMap* pMap = new CMap;
	pMap->Load(L"TutorialMap", L"texture\\Map\\TutorialScene\\Forest_Map_01.png");
	AddObject(pMap, GROUP_GAMEOBJ::FLOOR);

	CCameraManager::GetInst()->FadeIn(2.f);

	CCameraManager::GetInst()->SetBoundary(pMap->GetPos(), fPoint((float)m_pBgImage->GetWidth() * 2.f, (float)m_pBgImage->GetHeight() * 2.f));

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::FLOOR);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::BUILDING);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::DEFAULT);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::FLOOR);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::TILE);
}

void CScene_Tutorial::Exit()
{
	for (UINT i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; ++i)
	{
		if ((GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::ENEMY
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER_ATT_FX || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::ENEMY_ATT_FX
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::WEAPON) continue;

		ClearGroup((GROUP_GAMEOBJ)i);
	}

	CCameraManager::GetInst()->FadeOut(2.f);
}
