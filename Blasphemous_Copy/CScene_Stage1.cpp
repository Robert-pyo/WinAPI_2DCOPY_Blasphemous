#include "framework.h"
#include "CScene_Stage1.h"
#include "CBackground.h"
#include "CPlatform.h"
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
	// Background 积己
	CBackground* background = new CBackground;
	background->SetScale(fPoint(733.f, 238.f));
	background->SetImage(
		CResourceManager::getInst()->LoadD2DImage(L"Background", L"texture\\Map\\Background\\brotherhood-entrance-spritesheet.png"));
	background->SetTexLeftTop(fPoint(6.f, 779.f));
	AddObject(background, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CBackground* background_rock = background->Clone();
	background_rock->SetScale(fPoint(654.f, 306.f));
	background_rock->SetTexLeftTop(fPoint(5.f, 399.f));
	AddObject(background_rock, GROUP_GAMEOBJ::BACKGROUND_MIDDLE);

	// 敲饭捞绢 积己
	CPlayer* player = new CPlayer;
	player->init();
	AddObject(player, GROUP_GAMEOBJ::PLAYER);

	// 官蹿 积己
	CPlatform* floor1 = new CPlatform;
	AddObject(floor1, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor2 = floor1->Clone();
	floor2->SetPos(fPoint((floor1->GetPos().x + floor1->GetScale().x * 2.f), floor1->GetPos().y));
	AddObject(floor2, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor3 = floor1->Clone();
	floor3->SetPos(fPoint((floor2->GetPos().x + floor1->GetScale().x * 2.f), floor1->GetPos().y));
	AddObject(floor3, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor4 = floor1->Clone();
	floor4->SetPos(fPoint((floor3->GetPos().x + floor1->GetScale().x * 2.f), floor1->GetPos().y));
	AddObject(floor4, GROUP_GAMEOBJ::FLOOR);
	CPlatform* floor5 = floor1->Clone();
	floor5->SetPos(fPoint((floor4->GetPos().x + floor1->GetScale().x * 2.f), floor1->GetPos().y));
	AddObject(floor5, GROUP_GAMEOBJ::FLOOR);

	CCameraManager::getInst()->FollowTargetObj(player, true, true);
	CCameraManager::getInst()->InitCameraPos(fPoint(WINSIZE_X / 2.f, background->GetScale().y / 2.f));
	CCameraManager::getInst()->SetBoundary(fPoint(0.f, 0.f), fPoint(background->GetPos().x + background->GetScale().x * 4.f, 
											background->GetPos().y + background->GetScale().y * 2.f));

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::FLOOR);

	CCameraManager::getInst()->FadeIn(2.f);
}

void CScene_Stage1::Exit()
{
	ClearGroup(GROUP_GAMEOBJ::UI);
	ClearGroup(GROUP_GAMEOBJ::TILE);
	ClearGroup(GROUP_GAMEOBJ::DEFAULT);
	ClearGroup(GROUP_GAMEOBJ::BACKGROUND_BACK);
	ClearGroup(GROUP_GAMEOBJ::FLOOR);

	CCollisionManager::getInst()->Reset();
}
