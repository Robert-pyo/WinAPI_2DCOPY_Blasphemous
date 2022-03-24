#include "framework.h"
#include "CScene_Tutorial.h"
#include "CD2DImage.h"
#include "CBackground.h"
#include "CMap.h"

CScene_Tutorial::CScene_Tutorial()
{
	m_pMapImage = CResourceManager::GetInst()->LoadD2DImage(L"TutorialMap", L"texture\\Map\\TutorialScene\\Forest_Map_01.png");
	m_pBgImage = CResourceManager::GetInst()->LoadD2DImage(L"TutorialMapBg", L"texture\\Map\\TutorialScene\\Forest_Background.png");
}

CScene_Tutorial::~CScene_Tutorial()
{
}

void CScene_Tutorial::update()
{
	CScene::update();

	/*if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}

	if (PRESS_KEY('A'))
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

	// 플레이어 생성
	AddObject(CPlayer::GetPlayer(), GROUP_GAMEOBJ::PLAYER);

	CMap* pMap = new CMap;
	pMap->Load(L"TutorialMap", L"texture\\Map\\TutorialScene\\Forest_Map_01.png");
	AddObject(pMap, GROUP_GAMEOBJ::FLOOR);

	/*CCameraManager::GetInst()->SetLookAt(fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f));
	CCameraManager::GetInst()->FollowTargetObj(nullptr, false, false);
	CCameraManager::GetInst()->SetBoundary(false);*/
	CCameraManager::GetInst()->SetBoundary(fPoint(0.f, 0.f), fPoint((float)m_pBgImage->GetWidth() * 2.f, (float)m_pBgImage->GetHeight() * 2.f));

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
}

void CScene_Tutorial::Exit()
{
}
