#include "framework.h"
#include "CScene_Tutorial.h"
#include "CD2DImage.h"
#include "CBackground.h"
#include "CMap.h"

CScene_Tutorial::CScene_Tutorial()
{
	m_pBgImage = CResourceManager::GetInst()->LoadD2DImage(L"TutorialMapBg", L"texture\\Map\\TutorialScene\\Forest_Background.png");
}

CScene_Tutorial::~CScene_Tutorial()
{
	// �÷��̾ ������ ������ delete �� �� �ֵ���
	// �� �������� AddObject�Ǿ��� ���� ���Ϳ����� ������
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
	// Ÿ�� �ε�
	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"texture\\Map\\Tileset\\Tilemaps\\GroundTiles.tile";
	LoadTile(path);

	// �÷��̾� ����
	AddObject(CPlayer::GetPlayer(), GROUP_GAMEOBJ::PLAYER);

	CBackground* pBackground = new CBackground;
	pBackground->SetImage(m_pBgImage);
	pBackground->SetTexLeftTop(fPoint(0.f, 0.f));
	pBackground->SetScale(fPoint(m_pBgImage->GetWidth() * 2.f, m_pBgImage->GetHeight() * 2.f));
	AddObject(pBackground, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CMap* pMap = new CMap;
	pMap->Load(L"TutorialMap", L"texture\\Map\\TutorialScene\\Forest_Map_01.png");
	AddObject(pMap, GROUP_GAMEOBJ::FLOOR);


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
}
