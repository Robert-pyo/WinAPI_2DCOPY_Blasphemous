#include "framework.h"
#include "CScene_Stage1.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBall.h"
#include "CText_Time.h"
#include "CText_Score.h"
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
	// 플레이어 생성
	CPlayer* player = new CPlayer;
	player->init();
	AddObject(player, GROUP_GAMEOBJ::PLAYER);

	//CCameraManager::getInst()->FollowTargetObj(player);
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZE_X / 2.f, WINSIZE_Y / 2.f));
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);

	CCameraManager::getInst()->FadeIn(2.f);
}

void CScene_Stage1::Exit()
{
	ClearGroup(GROUP_GAMEOBJ::UI);
	ClearGroup(GROUP_GAMEOBJ::TILE);
	ClearGroup(GROUP_GAMEOBJ::DEFAULT);
	ClearGroup(GROUP_GAMEOBJ::BACKGROUND);
	ClearGroup(GROUP_GAMEOBJ::FLOOR);

	CCollisionManager::getInst()->Reset();
}
