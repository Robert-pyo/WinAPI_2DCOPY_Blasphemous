#include "framework.h"
#include "CScene_Boss.h"
#include "CMap.h"
#include "CWarpPoint.h"
#include "CBackground.h"
#include "CD2DImage.h"

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
	CWarpPoint* warpToCutScene = new CWarpPoint;
	warpToCutScene->SetName(L"BossCutScene");
	warpToCutScene->SetPos(fPoint(1517.f, 932.f));
	AddObject(warpToCutScene, GROUP_GAMEOBJ::DEFAULT);
}

void CScene_Boss::Enter()
{
	CUIManager::GetInst()->SetKeyControl(false);

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
	warpToChurch->SetPos(fPoint(pMap->GetPos().x + 100.f, pMap->GetPos().y + pMap->GetScale().y - 100.f));
	AddObject(warpToChurch, GROUP_GAMEOBJ::DEFAULT);

	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"Church")
	{
		CPlayer::GetPlayer()->SetPos(fPoint(warpToChurch->GetPos().x - 100.f, warpToChurch->GetPos().y));
	}

	SpawnObjects(this, "Player");

	CCameraManager::GetInst()->SetBoundary(pMap->GetPos(), pMap->GetPos() + pMap->GetScale());
	CCameraManager::GetInst()->InitCameraPos(
		fPoint(pMap->GetPos().x + pMap->GetScale().x - 600.f, pMap->GetPos().y + pMap->GetScale().y - 600.f));

	CCameraManager::GetInst()->FadeIn(2.0f);
}

void CScene_Boss::Exit()
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
