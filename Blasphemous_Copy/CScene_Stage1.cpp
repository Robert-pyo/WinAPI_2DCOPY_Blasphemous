#include "framework.h"
#include "CScene_Stage1.h"
#include "CBackground.h"
#include "CGround.h"
#include "CPrayerTable.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "AI.h"
#include "CState_Idle.h"
#include "CState_Trace.h"
#include "CSound.h"
#include "CWarpPoint.h"
#include "CPlayerSword.h"

CSound* pSound;

CScene_Stage1::CScene_Stage1()
{
	// 플레이어 생성
	CPlayer* pPlayer = new CPlayer;
	pPlayer->InitAnimation();
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	pPlayer->RegisterPlayer(pPlayer);

	CPlayerSword* pSword = new CPlayerSword;
	pSword->SetOwnerObj(pPlayer);
	AddObject(pSword, GROUP_GAMEOBJ::WEAPON);

	// 플레이어 무기와 능력 초기화
	pPlayer->SetWeapon(pSword);
	pPlayer->InitAbility();

	// 몬스터 생성
	CEnemy* monster = CEnemyFactory::CreateEnemy(ENEMY_TYPE::NORMAL, pPlayer->GetPos() + fPoint(300.0f, 0.f));
	AddObject(monster, GROUP_GAMEOBJ::ENEMY);
	AddObject(monster->GetEnemyInfo().pWeapon, GROUP_GAMEOBJ::WEAPON);

	CCameraManager::GetInst()->InitCameraPos(CPlayer::GetPlayer()->GetPos());
	CCameraManager::GetInst()->FollowTargetObj(CPlayer::GetPlayer(), true, true);
}

CScene_Stage1::~CScene_Stage1()
{
	if (nullptr != pSound)
		delete pSound;
}

void CScene_Stage1::update()
{
	CScene::update();

	if (PRESS_KEY_DOWN(VK_TAB))
	{
		ChangeToNextScene(GROUP_SCENE::TOOL);
	}
}

void CScene_Stage1::Enter()
{
	CSoundManager::GetInst()->AddSound(L"Tutorial_BGM", L"sound\\BGM\\Churches Field_MASTER.wav", true);
	CSoundManager::GetInst()->Play(L"Tutorial_BGM");

	// 타일 로딩
	wstring path = CPathManager::GetInst()->GetContentPath();
	path += L"texture\\Map\\Tileset\\Tilemaps\\GroundTiles.tile";
	LoadTile(path);

	// Background 생성
	CBackground* background = new CBackground;
	background->SetScale(fPoint(733.f, 238.f));
	background->SetImage(
		CResourceManager::GetInst()->LoadD2DImage(L"Background", L"texture\\Map\\TutorialScene\\Background\\brotherhood-entrance-spritesheet.png"));
	background->SetTexLeftTop(fPoint(6.f, 779.f));
	background->SetName(L"Background");
	AddObject(background, GROUP_GAMEOBJ::BACKGROUND_BACK);

	CBackground* background_rock = background->Clone();
	background_rock->SetScale(fPoint(654.f, 306.f));
	background_rock->SetTexLeftTop(fPoint(5.f, 399.f));
	background_rock->SetName(L"BG_Rock");
	AddObject(background_rock, GROUP_GAMEOBJ::BACKGROUND_MIDDLE);

	CBackground* background_bigDoor = background->Clone();
	background_bigDoor->SetScale(fPoint(361.f, 360.f));
	background_bigDoor->SetTexLeftTop(fPoint(3.f, 3.f));
	background_bigDoor->SetName(L"BG_BigDoor");
	AddObject(background_bigDoor, GROUP_GAMEOBJ::BACKGROUND_FRONT);


	// 바닥 생성
	CGround* floor1 = new CGround;
	floor1->SetPos(fPoint(background_bigDoor->GetPos().x + background_bigDoor->GetScale().x * 2.f + floor1->GetScale().x, floor1->GetPos().y));
	floor1->SetName(L"Floor1");
	AddObject(floor1, GROUP_GAMEOBJ::FLOOR);

	CGround* floor2 = floor1->Clone();
	floor2->SetPos(fPoint((floor1->GetPos().x + floor1->GetScale().x * 2.f - 1.f), floor1->GetPos().y));
	floor2->SetName(L"Floor2");
	AddObject(floor2, GROUP_GAMEOBJ::FLOOR);

	CGround* floor3 = floor1->Clone();
	floor3->SetPos(fPoint(floor1->GetPos().x - floor3->GetScale().x * 2.f, floor1->GetPos().y));
	floor3->SetName(L"Floor3");
	AddObject(floor3, GROUP_GAMEOBJ::FLOOR);

	CGround* floor4 = floor1->Clone();
	floor4->SetPos(fPoint((floor2->GetPos().x + floor1->GetScale().x * 2.f), floor1->GetPos().y));
	floor4->SetName(L"Floor4");
	AddObject(floor4, GROUP_GAMEOBJ::FLOOR);

	// 기도대 생성
	CPrayerTable* prayTable = new CPrayerTable;
	prayTable->SetPos(fPoint(floor4->GetPos().x - floor4->GetScale().x, floor4->GetPos().y - floor4->GetScale().y));
	prayTable->SetName(L"PrayerTable");
	AddObject(prayTable, GROUP_GAMEOBJ::BUILDING);

	// 스테이지 2 씬으로 이동하도록 워프포인트 설정
	CWarpPoint* warpPoint = new CWarpPoint;
	warpPoint->SetPos(fPoint(floor4->GetPos().x, floor4->GetPos().y));
	warpPoint->SetName(L"SceneChangePoint");
	AddObject(warpPoint, GROUP_GAMEOBJ::DEFAULT);

	CCameraManager::GetInst()->SetBoundary(fPoint(0.f, 0.f), fPoint(background->GetPos().x + background->GetScale().x * 4.f, background->GetPos().y + background->GetScale().y * 2.f));

	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ENEMY);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::FLOOR);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::BUILDING);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::DEFAULT);
	CCollisionManager::GetInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::FLOOR);

	CCameraManager::GetInst()->FadeIn(3.f);
}

void CScene_Stage1::Exit()
{
	for (UINT i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; ++i)
	{
		if ((GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::ENEMY
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::PLAYER_ATT_FX || (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::ENEMY_ATT_FX
			|| (GROUP_GAMEOBJ)i == GROUP_GAMEOBJ::WEAPON) continue;

		ClearGroup((GROUP_GAMEOBJ)i);
	}

	CPlayer::GetPlayer()->SetPos(fPoint(CPlayer::GetPlayer()->GetPos().x - 100.f, CPlayer::GetPlayer()->GetPos().y));

	CSoundManager::GetInst()->Stop(L"Tutorial_BGM");

	CCameraManager::GetInst()->FadeOut(2.f);
}
