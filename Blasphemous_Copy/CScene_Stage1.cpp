#include "framework.h"
#include "CScene_Stage1.h"
#include "CBackground.h"
#include "CPlatform.h"
#include "CPrayerTable.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CSound.h"

CSound* pSound;

CScene_Stage1::CScene_Stage1()
{
}

CScene_Stage1::~CScene_Stage1()
{
	if (nullptr != pSound)
		delete pSound;
}

void CScene_Stage1::update()
{
	CScene::update();
}

void CScene_Stage1::Enter()
{
	// Background 생성
	CBackground* background = new CBackground;
	background->SetScale(fPoint(733.f, 238.f));
	background->SetImage(
		CResourceManager::getInst()->LoadD2DImage(L"Background", L"texture\\Map\\TutorialScene\\Background\\brotherhood-entrance-spritesheet.png"));
	background->SetTexLeftTop(fPoint(6.f, 779.f));
	AddObject(background, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CBackground* background_rock = background->Clone();
	background_rock->SetScale(fPoint(654.f, 306.f));
	background_rock->SetTexLeftTop(fPoint(5.f, 399.f));
	AddObject(background_rock, GROUP_GAMEOBJ::BACKGROUND_MIDDLE);

	CBackground* background_bigDoor = background->Clone();
	background_bigDoor->SetScale(fPoint(361.f, 360.f));
	background_bigDoor->SetTexLeftTop(fPoint(3.f, 3.f));
	AddObject(background_bigDoor, GROUP_GAMEOBJ::BUILDING);

	// 플레이어 생성
	CPlayer* player = new CPlayer;
	AddObject(player, GROUP_GAMEOBJ::PLAYER);

	// 바닥 생성
	CPlatform* floor1 = new CPlatform;
	floor1->SetPos(fPoint(background_bigDoor->GetPos().x + background_bigDoor->GetScale().x * 2.f + floor1->GetScale().x, floor1->GetPos().y));
	AddObject(floor1, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor2 = floor1->Clone();
	floor2->SetPos(fPoint((floor1->GetPos().x + floor1->GetScale().x * 2.f - 1.f), floor1->GetPos().y));
	AddObject(floor2, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor3 = floor1->Clone();
	floor3->SetPos(fPoint(floor1->GetPos().x - floor3->GetScale().x * 2.f, floor1->GetPos().y));
	AddObject(floor3, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor4 = floor1->Clone();
	floor4->SetPos(fPoint((floor2->GetPos().x + floor1->GetScale().x * 2.f), floor1->GetPos().y));
	AddObject(floor4, GROUP_GAMEOBJ::FLOOR);

	// 기도대 생성
	CPrayerTable* prayTable = new CPrayerTable;
	prayTable->SetPos(fPoint(floor4->GetPos().x - floor4->GetScale().x, floor4->GetPos().y - floor4->GetScale().y));
	prayTable->SetName(L"PrayerTable");
	AddObject(prayTable, GROUP_GAMEOBJ::BUILDING);

	//CCameraManager::getInst()->FollowTargetObj(player, true, true);
	CCameraManager::getInst()->InitCameraPos(fPoint(WINSIZE_X / 2.f, background->GetScale().y / 2.f));
	CCameraManager::getInst()->SetBoundary(fPoint(0.f, 0.f), fPoint(background->GetPos().x + background->GetScale().x * 4.f, background->GetPos().y + background->GetScale().y * 2.f));

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::FLOOR);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::BUILDING);

	CCameraManager::getInst()->FadeIn(2.f);
}

void CScene_Stage1::Exit()
{
	ClearGroup(GROUP_GAMEOBJ::UI);
	ClearGroup(GROUP_GAMEOBJ::TILE);
	ClearGroup(GROUP_GAMEOBJ::DEFAULT);
	ClearGroup(GROUP_GAMEOBJ::BACKGROUND_BACK);
	ClearGroup(GROUP_GAMEOBJ::BACKGROUND_MIDDLE);
	ClearGroup(GROUP_GAMEOBJ::FLOOR);
	ClearGroup(GROUP_GAMEOBJ::BUILDING);

	CCollisionManager::getInst()->Reset();
}
