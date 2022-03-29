#include "framework.h"
#include "CScene_CS_BossApear.h"
#include "CBackground.h"
#include "CMap.h"
#include "CD2DImage.h"

CScene_CS_BossApear::CScene_CS_BossApear()
{
	m_pBgImg = CResourceManager::GetInst()->LoadD2DImage(L"BossRoom_Background", L"texture\\Map\\BossScene\\BossRoom_Background.png");
}

CScene_CS_BossApear::~CScene_CS_BossApear()
{
}

void CScene_CS_BossApear::init()
{
	SpawnObjects(L"Boss", "Piedad");
}

void CScene_CS_BossApear::Enter()
{
	CUIManager::GetInst()->SetKeyControl(false);

	CGameManager::GetInst()->SetDisableControl(true);

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

	SpawnObjects(L"Boss", "Player");
	CPlayer::GetPlayer()->SetPos(fPoint(1517.f, 932.f));
	CPlayer::GetPlayer()->SetDirection(fVector2D().Left());

	CCameraManager::GetInst()->SetBoundary(pMap->GetPos(), pMap->GetPos() + pMap->GetScale());
	CCameraManager::GetInst()->FollowTargetObj(nullptr, false, false);
	CCameraManager::GetInst()->InitCameraPos(fPoint(CPlayer::GetPlayer()->GetPos().x - 500.f, CPlayer::GetPlayer()->GetPos().y));

	CCameraManager::GetInst()->FadeIn(2.0f);
}

void CScene_CS_BossApear::Exit()
{
	CGameManager::GetInst()->SetDisableControl(false);
}
