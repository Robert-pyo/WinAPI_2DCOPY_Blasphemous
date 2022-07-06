#include "framework.h"
#include "CScene_Tutorial.h"
#include "CD2DImage.h"
#include "CBackground.h"
#include "CMap.h"
#include "CSpawnPoint.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CEnemyFactory.h"
#include "CWeapon.h"
#include "CWarpPoint.h"

CScene_Tutorial::CScene_Tutorial()
{
	m_pBgImage = CResourceManager::GetInst()->LoadD2DImage(L"TutorialMapBg", L"texture\\Map\\TutorialScene\\Forest_Background.png");
}

CScene_Tutorial::~CScene_Tutorial()
{
}

void CScene_Tutorial::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}
}

void CScene_Tutorial::init()
{
	SpawnObjects(this, "Acolyte");
}

void CScene_Tutorial::Enter()
{
	CUIManager::GetInst()->SetKeyControl(false);

	CSoundManager::GetInst()->AddSound(L"Forest_BGM", L"sound\\BGM\\Forest_MASTER.wav", true);
	CSoundManager::GetInst()->AddSound(L"Forest_Ambient", L"sound\\BGM\\Forest_ambient.wav", true);
	CSoundManager::GetInst()->Play(L"Forest_BGM");
	CSoundManager::GetInst()->Play(L"Forest_Ambient");
	CSoundManager::GetInst()->SetVolume(L"Forest_Ambient", 0.8f);

	// 타일 로딩
	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"texture\\Map\\Tileset\\Tilemaps\\GroundTiles.tile";
	LoadTile(path);

	SpawnObjects(this, "Player");

	CBackground* pBackground = new CBackground;
	pBackground->SetImage(m_pBgImage);
	pBackground->SetTexLeftTop(fPoint(0.f, 0.f));
	pBackground->SetScale(fPoint(m_pBgImage->GetWidth() * 2.f, m_pBgImage->GetHeight() * 2.f));
	AddObject(pBackground, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CMap* pMap = new CMap;
	pMap->Load(L"TutorialMap", L"texture\\Map\\TutorialScene\\Tutorial.png");
	AddObject(pMap, GROUP_GAMEOBJ::FLOOR);

	CWarpPoint* warpToChurch = new CWarpPoint;
	warpToChurch->SetName(L"Church");
	warpToChurch->SetPos(fPoint(0.f, pBackground->GetScale().y - 150.f));
	AddObject(warpToChurch, GROUP_GAMEOBJ::DEFAULT);

	if (CSceneManager::GetInst()->GetPrevScene() != nullptr &&
		CSceneManager::GetInst()->GetPrevScene()->GetName() == L"Church")
		CPlayer::GetPlayer()->SetPos(fPoint(warpToChurch->GetPos().x + 150.f, warpToChurch->GetPos().y - 100.f));

	CCameraManager::GetInst()->FadeIn(2.f);

	CCameraManager::GetInst()->InitCameraPos(CPlayer::GetPlayer()->GetPos() - fPoint(500.f, 200.f));
	//CCameraManager::GetInst()->FollowTargetObj(CPlayer::GetPlayer(), true, true);
	CCameraManager::GetInst()->SetBoundary(pMap->GetPos(), fPoint((float)m_pBgImage->GetWidth() * 2.f, (float)m_pBgImage->GetHeight() * 2.f));
}

void CScene_Tutorial::Exit()
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

	CSoundManager::GetInst()->Stop(L"Forest_BGM");
	CSoundManager::GetInst()->Stop(L"Forest_Ambient");

	//CCameraManager::GetInst()->FadeOut(2.f);
}
